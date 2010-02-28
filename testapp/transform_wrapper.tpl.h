/*

  phtrtest: Photoropter demo application

  Copyright (C) 2010 Robert Fendt

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

template <phtr::mem::Storage::type storage_T>
TransformWrapper<storage_T>::
TransformWrapper(const Settings& settings)
        : img_width_(0),
        img_height_(0),
        dst_width_(0),
        dst_height_(0),
        settings_(settings)
{
    load();
    init_transform();
    setup_transform();
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
load()
{
    vil_image_view<vil_pixel_t> loaded_img =
        vil_convert_to_component_order(
            vil_convert_to_n_planes(
                num_components_, vil_load(settings_.inp_file.c_str())
            )
        );

    // set image width and height
    img_width_ = loaded_img.ni();
    img_height_ = loaded_img.nj();
    dst_width_ = img_width_;
    dst_height_ = img_height_;

    // 'sanity checks' on ROI settings
    size_t sub_rect_x0 = settings_.sub_rect_x0;
    size_t sub_rect_y0 = settings_.sub_rect_y0;
    if (settings_.sub_rect && settings_.sub_rect_w <= img_height_ && settings_.sub_rect_h <= img_height_)
    {
        dst_width_ = settings_.sub_rect_w;
        dst_height_ = settings_.sub_rect_h;
    }
    if (sub_rect_x0 > img_height_ - dst_width_ || sub_rect_y0 > img_height_ - dst_height_)
    {
        sub_rect_x0 = 0;
        sub_rect_y0 = 0;
    }

    // allocate transfer buffers & attach views
    input_buffer_.reset(new buffer_t(img_width_, img_height_));
    input_view_.reset(new view_r_t(input_buffer_->data(), img_width_, img_height_));
    output_buffer_.reset(new buffer_t(dst_width_, dst_height_));
    output_view_.reset(new view_w_t(output_buffer_->data(), dst_width_, dst_height_));

    // attach a VIL view to the buffer
    vil_image_view<vil_pixel_t> vil_input_view(
        static_cast<vil_pixel_t*>(input_buffer_->data()), img_width_, img_height_, 1, 1, img_width_, 1
    );

    // tell VIL to convert/copy data into the Photoropter buffer
    vil_input_view.deep_copy(loaded_img);
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
init_transform()
{
    switch (settings_.interp_type)
    {
        case Interpolation::nearest_neighbour:
            image_transform_.reset(new transform_nn_t(*input_view_, *output_view_));
            break;

        case Interpolation::bilinear:
            image_transform_.reset(new transform_bilinear_t(*input_view_, *output_view_));
            break;

        case Interpolation::lanczos:
        default:
            image_transform_.reset(new transform_lanczos_t(*input_view_, *output_view_));
            transform_lanczos_t& transform = dynamic_cast<transform_lanczos_t&>(*image_transform_);
            transform.interpolator().set_support(settings_.lanczos_support);
            break;
    }
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
setup_transform()
{
    // setup sensor gain function (e.g. gamma or EMOR)
    set_gainfunc();

    // add transformation models
    add_models();

    // set oversampling
    image_transform_->set_sampling_fact(settings_.oversampling);
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
set_gainfunc()
{
    using namespace phtr;

    switch (settings_.gainfunc)
    {
        case GainFunc::invemor:
            {
                gamma::GammaInvEMOR emor_func;
                util::SetParam<gamma::GammaEMORBase::coeff_iter_t> coeff_iter = emor_func.set_params();

                for (size_t i = 0; i < settings_.emor_coeffs.size(); ++i)
                {
                    double coeff = settings_.emor_coeffs[i];
                    coeff_iter = coeff_iter(coeff);
                }

                image_transform_->set_gamma(emor_func);
            }

            break;

        case GainFunc::emor:
            {
                gamma::GammaEMOR emor_func;
                util::SetParam<gamma::GammaEMORBase::coeff_iter_t> coeff_iter = emor_func.set_params();

                for (size_t i = 0; i < settings_.emor_coeffs.size(); ++i)
                {
                    double coeff = settings_.emor_coeffs[i];
                    coeff_iter = coeff_iter(coeff);
                }

                image_transform_->set_gamma(emor_func);
            }

            break;

        case GainFunc::gamma:
            image_transform_->set_gamma(gamma::GammaGeneric(settings_.gamma));
            break;

        case GainFunc::srgb:
        default:
            image_transform_->set_gamma(gamma::GammaSRGB());
            break;
    }
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
add_models()
{
    using namespace phtr;

    double image_aspect = input_view_->aspect_ratio();
    double param_aspect(0);
    if (settings_.param_aspect_override)
    {
        param_aspect = settings_.param_aspect;
    }
    else
    {
        // if no aspect explicitely given, assume landscape aspect ratio of input image
        param_aspect = (image_aspect > 1) ? image_aspect : (1 / image_aspect);
    }

    double x0 = settings_.x0 / input_view_->height();
    double y0 = settings_.y0 / input_view_->height();

    if (settings_.ptlens_corr)
    {
        model::PTLensGeomModel ptlens_mod(param_aspect,
                                          image_aspect,
                                          settings_.param_crop,
                                          settings_.image_crop);
        if (settings_.ptlens_params.size() == 4)
        {
            ptlens_mod.set_model_params(settings_.ptlens_params[0],
                                        settings_.ptlens_params[1],
                                        settings_.ptlens_params[2],
                                        settings_.ptlens_params[3]);

        }
        else
        {
            ptlens_mod.set_model_params(settings_.ptlens_params[0],
                                        settings_.ptlens_params[1],
                                        settings_.ptlens_params[2]);
        }
        ptlens_mod.set_centre_shift(x0, y0);

        image_transform_->geom_queue().add_model(ptlens_mod);

        typedef phtr::mem::ColourTupleRGB::channel_order_t channel_order_t;
        double a, b, c, d;
        ptlens_mod.get_model_params(channel_order_t::idx_green, a, b, c, d);
    }

    if (settings_.vignetting_corr)
    {
        using model::HuginVignettingModel;
        // this time, the other way round. first add the model, then modify settings
        HuginVignettingModel vign_mod(param_aspect,
                                      image_aspect,
                                      settings_.param_crop,
                                      settings_.image_crop);

        // add model to queue and get reference to the internal object
        HuginVignettingModel& int_vign_mod = dynamic_cast<HuginVignettingModel&>(
                                                 image_transform_->colour_queue().add_model(vign_mod));

        int_vign_mod.set_model_params(settings_.vignetting_params[0],
                                      settings_.vignetting_params[1],
                                      settings_.vignetting_params[2]);
        int_vign_mod.set_centre_shift(x0, y0);
        // read the parameters back
        double a, b, c;
        int_vign_mod.get_model_params(a, b, c);

    }
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
do_transform()
{
    image_transform_->do_transform();
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
save()
{
    vil_image_view<vil_pixel_t> vil_output_view
    (static_cast<vil_pixel_t*>(output_buffer_->data()), dst_width_, dst_height_, 1, 1, dst_width_, 1);

    vil_save(vil_output_view, settings_.outp_file.c_str());
}
