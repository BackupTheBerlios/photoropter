/*
*
* Sample program to demonstrate basic usage of Photoropter.
*
* (c) 2010 by Robert Fendt
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
#include <photoropter/channel_storage.h>
#include <photoropter/image_interpolator.h>
#include <photoropter/image_transform.h>
#include <photoropter/colour_correction_model.h>
#include <photoropter/geom_correction_model.h>
#include <photoropter/colour_correction_model.h>

#include <ctime>
#include <string>
#include <vector>
#include <sstream>

struct Settings
{
    Settings()
            : ptlens_corr(false),
            ptlens_params(5, 0),
            vignetting_corr(false),
            vignetting_params(5, 0),
            param_aspect(0),
            param_crop(1.0),
            image_crop(1.0)
    {}

    bool ptlens_corr;
    std::vector<double> ptlens_params;
    bool vignetting_corr;
    std::vector<double> vignetting_params;
    double param_aspect;
    double param_crop;
    double image_crop;
    std::string inp_file;
    std::string outp_file;
};

bool parse_command_line(int argc, char* argv[], Settings& settings)
{

    try
    {

        po::options_description opt_desc("Allowed options");
        opt_desc.add_options()
        ("help", "show options")
        ("ptlens", po::value<std::string>(), "Set PTLens correction model parameters: a;b;c;x0;y0")
        ("vignetting", po::value<std::string>(), "Set vignetting correction parameters: a;b;c;x0;y0")
        ("param-aspect", po::value<double>(), "Aspect ratio used for parameter calibration")
        ("param-crop", po::value<double>(), "Crop factor used for parameter calibration")
        ("image-crop", po::value<double>(), "Diagonal image crop factor")
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
            std::cerr << opt_desc << "\n";
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

            if (not(param_idx == 3 or param_idx == 5))
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

            if (not(param_idx == 3 or param_idx == 5))
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

    }
    catch (po::invalid_command_line_syntax& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

template <phtr::Storage::type storage_type, typename vil_channel_t>
void convert(const Settings& settings)
{
    using namespace phtr;

    // typedefs and constants
    typedef ImageBuffer<storage_type> buffer_t;
    typedef MemImageViewR<storage_type> view_r_t;
    typedef MemImageViewW<storage_type> view_w_t;
    typedef typename view_w_t::iter_t iter_t;
    typedef ImageInterpolator<Interpolation::bilinear, view_r_t> interp_t;
    typedef ImageTransform<interp_t, view_w_t, 2> transform_t;

    // load the input image
    std::cerr << "Loading test image." << std::endl;
    vil_image_view<vil_rgb<vil_channel_t> > loaded_img =
        vil_convert_to_component_order(
            vil_convert_to_n_planes(
                3, vil_convert_stretch_range(
                    vil_channel_t(), vil_load(settings.inp_file.c_str())
                )
            )
        );

    // image size
    size_t img_width = loaded_img.ni();
    size_t img_height = loaded_img.nj();

    // create image buffers
    std::cerr << "Creating buffers for Photoropter." << std::endl;
    // input buffer
    buffer_t src_img_buf(img_width, img_height);
    view_r_t src_img_view(src_img_buf.data(), img_width, img_height);
    // output buffer
    buffer_t dst_img_buf(img_width, img_height, true);
    view_w_t dst_img_view(dst_img_buf.data(), img_width, img_height);

    // attach VIL views for I/O
    vil_image_view<vil_rgb<vil_channel_t> > vil_src_view
    (static_cast<vil_rgb<vil_channel_t>*>(src_img_buf.data()), img_width, img_height, 1, 1, img_width, 1);
    vil_image_view<vil_rgb<vil_channel_t> > vil_dst_view
    (static_cast<vil_rgb<vil_channel_t>*>(dst_img_buf.data()), img_width, img_height, 1, 1, img_width, 1);

    // copy data to input buffer
    std::cerr << "Copying image to buffer." << std::endl;
    vil_src_view.deep_copy(loaded_img);

    // image transformation object
    transform_t transform(src_img_view, dst_img_view);

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
        PTLensGeomModel ptlens_mod(param_aspect,
                                   image_aspect,
                                   settings.param_crop,
                                   settings.image_crop);
        ptlens_mod.set_model_params(settings.ptlens_params[0],
                                    settings.ptlens_params[1],
                                    settings.ptlens_params[2],
                                    1.0,
                                    settings.ptlens_params[3],
                                    settings.ptlens_params[4]);

        transform.geom_queue().add_model(ptlens_mod);
    }

    if (settings.vignetting_corr)
    {
        HuginVignettingModel vign_mod(param_aspect,
                                      image_aspect,
                                      settings.param_crop,
                                      settings.image_crop);
        vign_mod.set_model_params(settings.vignetting_params[0],
                                  settings.vignetting_params[1],
                                  settings.vignetting_params[2],
                                  settings.vignetting_params[3],
                                  settings.vignetting_params[4]);

        transform.colour_queue().add_model(vign_mod);
    }

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
            convert<phtr::Storage::rgb_8_inter, vxl_uint_8>(settings);
        }
        else
        {
            std::cerr << "Performing 16bit conversion." << std::endl;
            convert<phtr::Storage::rgb_16_inter, vxl_uint_16>(settings);
        }

    }

    return 0;
}
