/*

  phtrtest: Photoropter demo application

  Copyright (C) 2010 Robert Fendt

  Usage example :
  phtrtest --gain-func emor --param-aspect 1.5333 --vignetting 0:0:-0.3 --ptlens 0:0.00987:-0.05127 in.jpg out.jpg

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "parseconf.h"

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
#include <iostream>

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
