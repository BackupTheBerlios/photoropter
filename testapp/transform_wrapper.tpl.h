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
    log("Load image data.");
    load();
    log("Init transformation structures.");
    init_transform();
    log("Setup transformation.");
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
    std::stringstream sstr;
    sstr << "Image dimensions: " << img_width_ << "x" << img_height_;
    log(sstr.str());

    // 'sanity checks' on ROI settings
    size_t sub_rect_x0 = settings_.sub_rect_x0;
    size_t sub_rect_y0 = settings_.sub_rect_y0;
    if(settings_.sub_rect && settings_.sub_rect_w <= img_height_ && settings_.sub_rect_h <= img_height_)
    {
        dst_width_ = settings_.sub_rect_w;
        dst_height_ = settings_.sub_rect_h;
    }
    if(sub_rect_x0 > img_height_ - dst_width_ || sub_rect_y0 > img_height_ - dst_height_)
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
    unsigned int width = static_cast<unsigned int>(img_width_);
    unsigned int height = static_cast<unsigned int>(img_height_);
    vil_image_view<vil_pixel_t> vil_input_view(
        static_cast<vil_pixel_t*>(input_buffer_->data()), width, height, 1, 1, width, 1
    );

    // tell VIL to convert/copy data into the Photoropter buffer
    vil_input_view.deep_copy(loaded_img);
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
init_transform()
{
    using phtr::Interpolation;

    image_transform_.reset(phtr::IImageTransform::get_instance(settings_.interp_type, *input_view_, *output_view_));

    // the switch is mainly used for logging (and for setting the lanczos support)
    switch(settings_.interp_type)
    {
        case Interpolation::nearest_neighbour:
            log("Use nearest neighbour interpolation.");
            break;

        case Interpolation::bilinear:
            log("Use bilinear interpolation.");
            break;

        case Interpolation::lanczos:
        default:
            std::stringstream sstr;
            sstr << "Use Lanczos interpolation, support = " << settings_.lanczos_support;
            log(sstr.str());

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
    std::stringstream sstr;
    sstr << "Set (over-)sampling factor: " << settings_.oversampling;
    log(sstr.str());
    image_transform_->set_sampling_fact(settings_.oversampling);
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
set_gainfunc()
{
    using namespace phtr;

    switch(settings_.gainfunc)
    {
        case GainFunc::invemor:
            log("Use inverse EMOR gain function.");
            {
                gamma::GammaInvEMOR emor_func;
                util::SetParam<gamma::GammaEMORBase::coeff_iter_t> coeff_iter = emor_func.set_params();

                for(size_t i = 0; i < settings_.emor_coeffs.size(); ++i)
                {
                    double coeff = settings_.emor_coeffs[i];
                    coeff_iter = coeff_iter(coeff);
                }

                image_transform_->set_gamma(emor_func);
            }

            break;

        case GainFunc::emor:
            log("Use EMOR gain function.");
            {
                gamma::GammaEMOR emor_func;
                util::SetParam<gamma::GammaEMORBase::coeff_iter_t> coeff_iter = emor_func.set_params();

                for(size_t i = 0; i < settings_.emor_coeffs.size(); ++i)
                {
                    double coeff = settings_.emor_coeffs[i];
                    coeff_iter = coeff_iter(coeff);
                }

                image_transform_->set_gamma(emor_func);
            }

            break;

        case GainFunc::gamma:
            log("Use generic gamma gain function.");
            image_transform_->set_gamma(gamma::GammaGeneric(settings_.gamma));
            break;

        case GainFunc::srgb:
        default:
            log("Use sRGB gamma gain function.");
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
    if(settings_.param_aspect_override)
    {
        param_aspect = settings_.param_aspect;
        std::stringstream sstr;
        sstr << "Override parameter aspect: " << param_aspect;
        log(sstr.str());
    }
    else
    {
        // if no aspect explicitely given, assume landscape aspect ratio of input image
        param_aspect = (image_aspect > 1) ? image_aspect : (1 / image_aspect);

        std::stringstream sstr;
        sstr << "Assume parameter aspect: " << param_aspect;
        log(sstr.str());
    }

    // calculate centre shift
    double x0 = static_cast<double>(settings_.x0) / static_cast<double>(input_view_->height());
    double y0 = static_cast<double>(settings_.y0) / static_cast<double>(input_view_->height());

    size_t idx_red = view_r_t::storage_info_t::mem_layout_t::idx_red;
    size_t idx_blue = view_r_t::storage_info_t::mem_layout_t::idx_blue;

    if(settings_.do_tca)
    {
        log("Add model: linear TCA correction.");
        model::ScalerGeomModel scaler_tca_mod(param_aspect,
                                              image_aspect,
                                              settings_.param_crop,
                                              settings_.image_crop);

        scaler_tca_mod.set_model_param_single(idx_red, settings_.tca_r);
        scaler_tca_mod.set_model_param_single(idx_blue, settings_.tca_b);

        image_transform_->geom_queue().add_model(scaler_tca_mod);
    }

    // apply PTLens TCA correction (fulla style)
    if(settings_.ptlens_tca_corr)
    {
        log("Add model: PTLens TCA correction.");
        model::PTLensGeomModel ptlens_tca_mod(param_aspect,
                                              image_aspect,
                                              settings_.param_crop,
                                              settings_.image_crop);

        ptlens_tca_mod.set_model_params(0, 0, 0);
        ptlens_tca_mod.set_model_params_single(idx_red, settings_.ptlens_r_params[0],
                                               settings_.ptlens_r_params[1],
                                               settings_.ptlens_r_params[2],
                                               settings_.ptlens_r_params[3]);
        ptlens_tca_mod.set_model_params_single(idx_blue, settings_.ptlens_b_params[0],
                                               settings_.ptlens_b_params[1],
                                               settings_.ptlens_b_params[2],
                                               settings_.ptlens_b_params[3]);

        ptlens_tca_mod.set_centre_shift(x0, y0);

        image_transform_->geom_queue().add_model(ptlens_tca_mod);
    }

    // apply PTLens geometric correction
    if(settings_.ptlens_corr)
    {
        log("Add model: PTLens geometric correction.");
        model::PTLensGeomModel ptlens_mod(param_aspect,
                                          image_aspect,
                                          settings_.param_crop,
                                          settings_.image_crop);
        if(settings_.ptlens_params.size() == 4)
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
    }

    //model::GeometryConvertGeomModel geom_conv_mod(image_aspect, settings_.image_crop);
    //geom_conv_mod.set_focal_lengths(8, 8);
    //image_transform_->geom_queue().add_model(geom_conv_mod);

    if(settings_.do_scale)
    {
        log("Add model: linear scaling factor.");
        model::ScalerGeomModel scaler_mod(param_aspect,
                                          image_aspect,
                                          settings_.param_crop,
                                          settings_.image_crop);

        scaler_mod.set_model_param(settings_.scale_fact);

        image_transform_->geom_queue().add_model(scaler_mod);
    }

    // apply vignetting correction
    if(settings_.vignetting_corr)
    {
        log("Add model: vignetting correction.");
        using model::HuginVignettingModel;
        // this time, the other way round. first add the model, then modify settings
        // (yes, this works, too)
        HuginVignettingModel tmp_vign_mod(param_aspect,
                                          image_aspect,
                                          settings_.param_crop,
                                          settings_.image_crop);

        // add the model to queue and get a reference to the internal object back
        HuginVignettingModel& vign_mod = dynamic_cast<HuginVignettingModel&>(
                                             image_transform_->colour_queue().add_model(tmp_vign_mod));

        vign_mod.set_model_params(settings_.vignetting_params[0],
                                  settings_.vignetting_params[1],
                                  settings_.vignetting_params[2]);
        vign_mod.set_centre_shift(x0, y0);
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
    unsigned int width = static_cast<unsigned int>(dst_width_);
    unsigned int height = static_cast<unsigned int>(dst_height_);
    vil_image_view<vil_pixel_t> vil_output_view
    (static_cast<vil_pixel_t*>(output_buffer_->data()), width, height, 1, 1, width, 1);

    vil_save(vil_output_view, settings_.outp_file.c_str());
}

template <phtr::mem::Storage::type storage_T>
void
TransformWrapper<storage_T>::
log(const std::string& msg)
{
    if(settings_.verbose)
    {
        std::cerr << msg << std::endl;
    }
}
