/*
*
* Quick&Dirty sample program to demonstrate basic usage of Photoropter.
*
* Usage example :
*
* phtrtest --gain-func emor --param-aspect 1.5333 --vignetting 0:0:-0.3 --ptlens 0:0.00987:-0.05127 in.jpg out.jpg
*
* Copyright (C) 2010 Robert Fendt
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

// Boost is used for parsing of program options.
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
namespace po = boost::program_options;

// VIL is needed for image file I/O
#include <vcl_iostream.h>
#include <vxl_config.h>
#include <vil/vil_rgb.h>
#include <vil/vil_load.h>
#include <vil/vil_save.h>
#include <vil/vil_convert.h>
#include <vil/vil_fill.h>
#include <vil/vil_copy.h>
#include <vil/vil_image_view.h>

// Now the Photoropter stuff
#include <photoropter/types.h>
#include <photoropter/mem_image_view_r.h>
#include <photoropter/mem_image_view_w.h>
#include <photoropter/image_buffer.h>
#include <photoropter/mem/channel_storage.h>
#include <photoropter/interpolator_nn.h>
#include <photoropter/interpolator_bilinear.h>
#include <photoropter/interpolator_lanczos.h>
#include <photoropter/image_transform.h>
#include <photoropter/model/colour_correction_model.h>
#include <photoropter/model/geom_correction_model.h>
#include <photoropter/version.h>

#include <ctime>
#include <string>
#include <vector>
#include <sstream>

struct Settings
{
    enum gainfunc_t
    {
        gf_srgb,
        gf_gamma,
        gf_emor,
        gf_invemor
    };

    Settings()
            : ptlens_corr(false),
            ptlens_params(5, 0),
            vignetting_corr(false),
            vignetting_params(5, 0),
            param_aspect(0),
            param_crop(1.0),
            image_crop(1.0),
            sub_rect(false),
            sub_rect_x0(0),
            sub_rect_y0(0),
            sub_rect_w(0),
            sub_rect_h(0),
            gamma(2.2),
            gainfunc(gf_srgb),
            oversampling(1)
    {}

    bool ptlens_corr;
    std::vector<double> ptlens_params;
    bool vignetting_corr;
    std::vector<double> vignetting_params;
    double param_aspect;
    double param_crop;
    double image_crop;
    bool sub_rect;
    size_t sub_rect_x0;
    size_t sub_rect_y0;
    size_t sub_rect_w;
    size_t sub_rect_h;
    double gamma;
    std::string inp_file;
    std::string outp_file;
    gainfunc_t gainfunc;
    std::vector<double> emor_coeffs;
    unsigned oversampling;
};

bool parse_command_line(int argc, char* argv[], Settings& settings)
{

    try
    {

        po::options_description opt_desc("Allowed options");
        opt_desc.add_options()
        ("help,h", "show options")
        ("ptlens", po::value<std::string>(), "Set PTLens correction model parameters: a:b:c[:x0:y0]")
        ("vignetting", po::value<std::string>(), "Set vignetting correction parameters: a:b:c[:x0:y0]")
        ("param-aspect", po::value<double>(), "Aspect ratio used for parameter calibration")
        ("param-crop", po::value<double>(), "Crop factor used for parameter calibration")
        ("image-crop", po::value<double>(), "Diagonal image crop factor")
        ("sub-rect", po::value<std::string>(), "Clip a sub-rectangle from the image: x0:y0:width:height")
        ("gain-func", po::value<std::string>(), "Type of gain function:\n"
         "  srgb    - sRGB gamma (default)\n"
         "  gamma   - generic gamma\n"
         "  emor    - EMOR\n"
         "  invemor - inverse EMOR.")
        ("gamma", po::value<double>(), "Gamma value (default: assume sRGB gamma)")
        ("emor-params", po::value<std::string>(), "EMOR parameters: h1[:h2[:h3...]]")
        ("oversample", po::value<unsigned>(), "Sampling factor (>= 1)")
        ("input-file", po::value<std::string>(), "Input file")
        ("output-file", po::value<std::string>(), "Output file");

        po::positional_options_description pos_opts;
        pos_opts.add("input-file", 1);
        pos_opts.add("output-file", 1);

        po::variables_map options_map;
        po::store(po::command_line_parser(argc, argv).
                  options(opt_desc).positional(pos_opts).run(), options_map);
        po::notify(options_map);

        if (options_map.count("help"))
        {
            std::cerr << opt_desc << std::endl;
            return false;
        }

        if (options_map.count("param-crop"))
        {
            settings.param_crop = options_map["param-crop"].as<double>();
        }

        if (options_map.count("param-aspect"))
        {
            settings.param_aspect = options_map["param-aspect"].as<double>();
        }

        if (options_map.count("image-crop"))
        {
            settings.image_crop = options_map["image-crop"].as<double>();
        }

        if (options_map.count("input-file"))
        {
            settings.inp_file = options_map["input-file"].as<std::string>();
        }
        else
        {
            std::cerr << "Error: no input file given" << std::endl;
            return false;
        }

        if (options_map.count("output-file"))
        {
            settings.outp_file = options_map["output-file"].as<std::string>();
        }
        else
        {
            std::cerr << "Error: no output file given" << std::endl;
            return false;
        }

        if (options_map.count("ptlens"))
        {
            settings.ptlens_corr = true;

            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["ptlens"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            size_t param_idx(0);
            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                std::stringstream sstr(*it);
                sstr >> settings.ptlens_params[param_idx++];
            }

            if (!(param_idx == 3 || param_idx == 5))
            {
                std::cerr << "Error: incorrent number of parameters for PTLens correction" << std::endl;
                return false;
            }

            std::cerr << "Performing PTLens correction: "
                      << settings.ptlens_params[0] << ":"
                      << settings.ptlens_params[1] << ":"
                      << settings.ptlens_params[2] << ":"
                      << settings.ptlens_params[3] << ":"
                      << settings.ptlens_params[4] << std::endl;
        }

        if (options_map.count("vignetting"))
        {
            settings.vignetting_corr = true;

            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["vignetting"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            size_t param_idx(0);
            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                std::stringstream sstr(*it);
                sstr >> settings.vignetting_params[param_idx++];
            }

            if (!(param_idx == 3 || param_idx == 5))
            {
                std::cerr << "Error: incorrent number of parameters for Vignetting correction" << std::endl;
                return false;
            }

            std::cerr << "Performing Vignetting correction: "
                      << settings.vignetting_params[0] << ":"
                      << settings.vignetting_params[1] << ":"
                      << settings.vignetting_params[2] << ":"
                      << settings.vignetting_params[3] << ":"
                      << settings.vignetting_params[4] << std::endl;
        }

        if (options_map.count("sub-rect"))
        {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["sub-rect"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            std::vector<size_t> rect_params(4, 0);

            size_t param_idx(0);
            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                std::stringstream sstr(*it);
                sstr >> rect_params[param_idx++];
            }

            if (!(param_idx == 4))
            {
                std::cerr << "Error: incorrent number of parameters for sub rectangle" << std::endl;
                return false;
            }

            settings.sub_rect_x0 = rect_params[0];
            settings.sub_rect_y0 = rect_params[1];
            settings.sub_rect_w = rect_params[2];
            settings.sub_rect_h = rect_params[3];
            settings.sub_rect = true;
        }

        if (options_map.count("gain-func"))
        {
            std::string opt = options_map["gain-func"].as<std::string>();
            if (opt == "srgb")
            {
                settings.gainfunc = Settings::gf_srgb;
            }
            else if (opt == "gamma")
            {
                settings.gainfunc = Settings::gf_gamma;
            }
            else if (opt == "emor")
            {
                settings.gainfunc = Settings::gf_emor;
            }
            if (opt == "invemor")
            {
                settings.gainfunc = Settings::gf_invemor;
            }
        }

        if (options_map.count("emor-params"))
        {
            typedef boost::tokenizer<boost::char_separator<char> > tokenizer_t;
            typedef boost::char_separator<char> separator_t;

            std::string param_string = options_map["emor-params"].as<std::string>();

            separator_t sep(":;");
            tokenizer_t tokens(param_string, sep);

            for (tokenizer_t::const_iterator it = tokens.begin(); it != tokens.end(); ++it)
            {
                double val;
                std::stringstream sstr(*it);
                sstr >> val;
                settings.emor_coeffs.push_back(val);
            }

        }

        if (options_map.count("gamma"))
        {
            settings.gamma = options_map["gamma"].as<double>();
        }

        if (options_map.count("oversample"))
        {
            settings.oversampling = options_map["oversample"].as<unsigned>();
        }

    }
    catch (po::unknown_option& e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << "Try option '--help'" << std::endl;
        return false;
    }
    catch (po::invalid_command_line_syntax& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

template <phtr::mem::Storage::type storage_type, typename vil_channel_t>
void convert(const Settings& settings)
{
    using namespace phtr;

    std::cerr << "Using Photoropter version " << PHTR_VERSION << std::endl;

    // typedefs and constants
    typedef ImageBuffer<storage_type> buffer_t;
    typedef MemImageViewR<storage_type> view_r_t;
    typedef MemImageViewW<storage_type> view_w_t;
    typedef typename view_w_t::iter_t iter_t;
//    typedef InterpolatorNN<view_r_t> interp_t;
    typedef InterpolatorBilinear<view_r_t> interp_t;
//    typedef InterpolatorLanczos<view_r_t> interp_t;
    typedef ImageTransform<interp_t, view_w_t> transform_t;

    // load the input image
    std::cerr << "Loading test image." << std::endl;
    vil_image_view<vil_rgb<vil_channel_t> > loaded_img =
        vil_convert_to_component_order(
            vil_convert_to_n_planes(3, vil_load(settings.inp_file.c_str())
                                   )
        );

    // image size
    size_t img_width = loaded_img.ni();
    size_t img_height = loaded_img.nj();
    size_t dst_width = img_width;
    size_t dst_height = img_height;
    // 'sanity checks' on ROI settings
    size_t sub_rect_x0 = settings.sub_rect_x0;
    size_t sub_rect_y0 = settings.sub_rect_y0;
    if (settings.sub_rect && settings.sub_rect_w <= img_width && settings.sub_rect_h <= img_height)
    {
        dst_width = settings.sub_rect_w;
        dst_height = settings.sub_rect_h;
    }
    if (sub_rect_x0 > img_width - dst_width || sub_rect_y0 > img_height - dst_height)
    {
        sub_rect_x0 = 0;
        sub_rect_y0 = 0;
    }

    // create image buffers
    std::cerr << "Creating buffers for Photoropter." << std::endl;
    // input buffer
    buffer_t src_img_buf(img_width, img_height);
    view_r_t src_img_view(src_img_buf.data(), img_width, img_height);
    // output buffer
    buffer_t dst_img_buf(dst_width, dst_height, true);
    view_w_t dst_img_view(dst_img_buf.data(), dst_width, dst_height);
    dst_img_view.set_parent_window(settings.sub_rect_x0, settings.sub_rect_y0, img_width, img_height);

    // attach VIL views for I/O
    vil_image_view<vil_rgb<vil_channel_t> > vil_src_view
    (static_cast<vil_rgb<vil_channel_t>*>(src_img_buf.data()), img_width, img_height, 1, 1, img_width, 1);
    vil_image_view<vil_rgb<vil_channel_t> > vil_dst_view
    (static_cast<vil_rgb<vil_channel_t>*>(dst_img_buf.data()), dst_width, dst_height, 1, 1, dst_width, 1);

    // copy data to input buffer
    std::cerr << "Copying image to buffer." << std::endl;
    vil_src_view.deep_copy(loaded_img);

    // image transformation object
    transform_t transform(src_img_view, dst_img_view);

    // this only works on Lanczos interpolated transformation objects.
//    transform.interpolator().set_support(3);

    // set gain function
    switch (settings.gainfunc)
    {
        case Settings::gf_invemor:
            {
                gamma::GammaInvEMOR emor_func;
                util::SetParam<gamma::GammaEMORBase::coeff_iter_t> coeff_iter = emor_func.set_params();

                std::cerr << "Applying inverse EMOR curve." << std::endl;
                std::cerr << "EMOR coefficients:";

                for (size_t i = 0; i < settings.emor_coeffs.size(); ++i)
                {
                    double coeff = settings.emor_coeffs[i];
                    coeff_iter = coeff_iter(coeff);

                    std::cerr << " " << coeff;
                }
                std::cerr << std::endl;

                transform.set_gamma(emor_func);
            }

            break;

        case Settings::gf_emor:
            {
                gamma::GammaEMOR emor_func;
                util::SetParam<gamma::GammaEMORBase::coeff_iter_t> coeff_iter = emor_func.set_params();

                std::cerr << "Applying EMOR curve." << std::endl;
                std::cerr << "EMOR coefficients:";

                for (size_t i = 0; i < settings.emor_coeffs.size(); ++i)
                {
                    double coeff = settings.emor_coeffs[i];
                    coeff_iter = coeff_iter(coeff);

                    std::cerr << " " << coeff;
                }
                std::cerr << std::endl;

                transform.set_gamma(emor_func);
            }

            break;

        case Settings::gf_gamma:
            std::cerr << "Assuming generic image gamma of " << settings.gamma << "." << std::endl;
            transform.set_gamma(gamma::GammaGeneric(settings.gamma));
            break;

        case Settings::gf_srgb:
        default:
            std::cerr << "Assuming sRGB gamma." << std::endl;
            transform.set_gamma(gamma::GammaSRGB());
            break;
    }

    // add correction models
    double image_aspect = src_img_view.aspect_ratio();
    double param_aspect(0);
    if (settings.param_aspect)
    {
        param_aspect = settings.param_aspect;
    }
    else
    {
        param_aspect = image_aspect;
    }

    if (settings.ptlens_corr)
    {
        model::PTLensGeomModel ptlens_mod(param_aspect,
                                          image_aspect,
                                          settings.param_crop,
                                          settings.image_crop);
        ptlens_mod.set_model_params(settings.ptlens_params[0],
                                    settings.ptlens_params[1],
                                    settings.ptlens_params[2]);
        ptlens_mod.set_centre_shift(settings.ptlens_params[3],
                                    settings.ptlens_params[4]);

        transform.geom_queue().add_model(ptlens_mod);

        typedef phtr::mem::ColourTupleRGB::channel_order_t channel_order_t;
        double a, b, c, d;
        ptlens_mod.get_model_params(channel_order_t::idx_green, a, b, c, d);
        std::cerr << "PTLens parameters: " << a << " " << b << " " << c << std::endl;
    }

    if (settings.vignetting_corr)
    {
        using model::HuginVignettingModel;
        // this time, the other way round. first add the model, then modify settings
        HuginVignettingModel vign_mod(param_aspect,
                                      image_aspect,
                                      settings.param_crop,
                                      settings.image_crop);

        // add model to queue and get reference to the internal object
        HuginVignettingModel& int_vign_mod = dynamic_cast<HuginVignettingModel&>(
                                                 transform.colour_queue().add_model(vign_mod));

        int_vign_mod.set_model_params(settings.vignetting_params[0],
                                      settings.vignetting_params[1],
                                      settings.vignetting_params[2]);
        int_vign_mod.set_centre_shift(settings.vignetting_params[3],
                                      settings.vignetting_params[4]);
        // read the parameters back
        double a, b, c;
        int_vign_mod.get_model_params(a, b, c);
        std::cerr << "Vignetting parameters: " << a << " " << b << " " << c << std::endl;

    }

    // set oversampling
    transform.set_sampling_fact(settings.oversampling);

    // perform transformation
    time_t t0 = time(0);
    std::cerr << "Transforming." << std::endl;
    transform.do_transform();
    time_t t1 = time(0);

    std::cerr << "Time taken: " << difftime(t1, t0) << " seconds." << std::endl;

    std::cerr << "Saving output image." << std::endl;
    vil_save(vil_dst_view, settings.outp_file.c_str());
}

int main(int argc, char* argv[])
{
    Settings settings;

    if (!parse_command_line(argc, argv, settings))
    {
        return 1;
    }
    else
    {
        vil_pixel_format img_format;

        {
            vil_image_resource_sptr img_res = vil_load_image_resource(settings.inp_file.c_str());
            img_format = img_res->pixel_format();
        }

        if (img_format == VIL_PIXEL_FORMAT_BYTE)
        {
            std::cerr << "Performing 8bit conversion." << std::endl;
            convert<phtr::mem::Storage::rgb_8_inter, vxl_uint_8>(settings);
        }
        else
        {
            std::cerr << "Performing 16bit conversion." << std::endl;
            convert<phtr::mem::Storage::rgb_16_inter, vxl_uint_16>(settings);
        }

    }

    return 0;
}
