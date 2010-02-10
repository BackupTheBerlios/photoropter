/*

Photoropter: lens correction for digital cameras

Copyright (c) 2010 Robert Fendt

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

namespace phtr
{

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    ImageTransform
    (const typename ImageTransform::image_view_t& image_view_r, image_view_w_t& image_view_w)
            : interpolator_(image_view_r),
            image_view_w_(image_view_w),
            outp_img_width_(image_view_w.width()),
            outp_img_height_(image_view_w.height()),
            storage_info_(outp_img_width_, outp_img_height_),
            min_chan_val_(static_cast<interp_channel_t>(storage_info_.min_val)),
            max_chan_val_(static_cast<interp_channel_t>(storage_info_.max_val)),
            gamma_(2.2)
    {
        //NIL

        // gamma lookup table
        gam_val_a_.resize(101);
        gam_val_b_.resize(101);
        inv_gam_val_a_.resize(101);
        inv_gam_val_b_.resize(101);
        for (int i = 0; i < 101; ++i)
        {
            float v1 = static_cast<float>(i) / 100;
            float v2 = static_cast<float>(i + 1) / 100;
            float g1 = gamma(v1);
            float g2 = gamma(v2);
            float a = (g2 - g1) / (v2 - v1);
            gam_val_a_[i] = a;
            gam_val_b_[i] = g1 - a * v1;

            float ig1 = inv_gamma(v1);
            float ig2 = inv_gamma(v2);
            float ia = (ig2 - ig1) / (v2 - v1);
            inv_gam_val_a_[i] = ia;
            inv_gam_val_b_[i] = ig1 - ia * v1;
        }
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    void
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    do_transform
    ()
    {
        // oversampling parameters
        const interp_coord_t sampling_fact = static_cast<interp_coord_t>(oversampling);
        const interp_coord_t sampling_step_x = 1.0 / sampling_fact;
        const interp_coord_t sampling_step_y = 1.0 / sampling_fact;
        const interp_channel_t channel_scaling = sampling_step_x * sampling_step_y;

        // parent window size and offset
        coord_t p_offs_x(0);
        coord_t p_offs_y(0);
        coord_t p_width(0);
        coord_t p_height(0);
        image_view_w_.get_parent_window(p_offs_x, p_offs_y, p_width, p_height);

        const interp_coord_t parent_x_max = static_cast<interp_coord_t>(p_width - 1);
        const interp_coord_t parent_y_max = static_cast<interp_coord_t>(p_height - 1);

        // coordinate transformation parameters
        interp_coord_t aspect_ratio = interpolator_.aspect_ratio();
        interp_coord_t scale_x = 2.0 * aspect_ratio / parent_x_max;
        interp_coord_t scale_y = 2.0 / parent_y_max;

        // running index variables are i (x direction) and j (y direction)
        // limits are: i0 <= i < i_limit and j0 <= j < j_limit
        coord_t i0(0);
        coord_t j0(0);
        coord_t i_limit(0);
        coord_t j_limit(0);

        // determine limits from image's region of interest
        image_view_w_.get_roi(i0, j0, i_limit, j_limit);

        // main transformation loop
        // this variable has to be signed for OpenMP 2.0, which is the only
        // version supported by MSVC (no real problem, e.g. 'long' should be big enough anyway).
        omp_coord_t j(0);
        coord_t i(0);
#ifdef HAVE_OPENMP
#pragma omp parallel for private (i)
#endif
        for (j = static_cast<omp_coord_t>(j0); j < static_cast<omp_coord_t>(j_limit); ++j) // line loop
        {

            // write-access iterator for this line
            typename image_view_w_t::iter_t iter(image_view_w_.get_iter(i0, j));

            for (i = i0; i < i_limit; ++i) // pixel loop
            {
                // current pixel position
                interp_coord_t cur_pixel_x(i);
                interp_coord_t cur_pixel_y(j);

                /* scaled coordinates (in the interpolator coordinates system) */
                interp_coord_t dst_x(0);
                interp_coord_t dst_y(0);

                // coordinates transformed to source image
                interp_coord_t src_x_r(0);
                interp_coord_t src_y_r(0);
                interp_coord_t src_x_g(0);
                interp_coord_t src_y_g(0);
                interp_coord_t src_x_b(0);
                interp_coord_t src_y_b(0);

                // channel values
                interp_channel_t val_r(0);
                interp_channel_t val_g(0);
                interp_channel_t val_b(0);

                // channel factors
                double fact_r(1.0);
                double fact_g(1.0);
                double fact_b(1.0);

                // prepare (over-)sampling loop
                interp_coord_t cur_samp_x(0);
                interp_coord_t ini_samp_x(cur_pixel_x - 0.5 + (1.0 / (2 * sampling_fact)));
                interp_coord_t cur_samp_y(cur_pixel_y - 0.5 + (1.0 / (2 * sampling_fact)));
                unsigned int u(0);
                unsigned int v(0);

                for (v = 0; v < oversampling; ++v)
                {
                    cur_samp_x = ini_samp_x;

                    for (u = 0; u < oversampling; ++u)
                    {
                        // get scaled coordinates (in the interpolator coordinates system)
                        dst_x = ((cur_samp_x + p_offs_x) * scale_x) - aspect_ratio;
                        dst_y = ((cur_samp_y + p_offs_y) * scale_y) - 1.0;

                        // get coordinates transformed to source image
                        geom_queue_.get_source_coords(dst_x, dst_y,
                                                      src_x_r, src_y_r,
                                                      src_x_g, src_y_g,
                                                      src_x_b, src_y_b);

                        // get channel values and correction factors
                        colour_queue_.get_correction_factors(src_x_r, src_y_r,
                                                             src_x_g, src_y_g,
                                                             src_x_b, src_y_b,
                                                             fact_r, fact_g, fact_b);

                        val_r += normalise(interpolator_.get_px_val(Channel::red, src_x_r, src_y_r)) * fact_r;
                        val_g += normalise(interpolator_.get_px_val(Channel::green, src_x_g, src_y_g)) * fact_g;
                        val_b += normalise(interpolator_.get_px_val(Channel::blue, src_x_b, src_y_b)) * fact_b;

                        cur_samp_x += sampling_step_x;
                    } // (inner) oversampling loop

                    cur_samp_y += sampling_step_y;
                } // (outer) oversampling loop

                // scale channel values (due to oversampling)
                val_r *= channel_scaling;
                val_g *= channel_scaling;
                val_b *= channel_scaling;

                // deal with clipping
                clip_vals(val_r, val_g, val_b);

                // write channel values
                iter.write_px_val(Channel::red, static_cast<channel_storage_t>(unnormalise(val_r)));
                iter.write_px_val(Channel::green, static_cast<channel_storage_t>(unnormalise(val_g)));
                iter.write_px_val(Channel::blue, static_cast<channel_storage_t>(unnormalise(val_b)));

                // increment iterator position
                iter.inc_x();

            } // column loop

        } // line loop

    } //  ImageTransform<...>::do_transform()

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    GeomCorrectionQueue&
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    geom_queue()
    {
        return geom_queue_;
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    ColourCorrectionQueue&
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    colour_queue()
    {
        return colour_queue_;
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    void
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    clip_vals(interp_channel_t& val_r,
              interp_channel_t& val_g,
              interp_channel_t& val_b)
    {
        if (val_r > 1.0)
        {
            val_r = 1.0;
        }

        if (val_g > 1.0)
        {
            val_g = 1.0;
        }

        if (val_b > 1.0)
        {
            val_b = 1.0;
        }

        if (val_r < 0.0)
        {
            val_r = 0.0;
        }

        if (val_g < 0.0)
        {
            val_g = 0.0;
        }

        if (val_b < 0.0)
        {
            val_b = 0.0;
        }
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    interp_channel_t
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    normalise(interp_channel_t value)
    {
        return fast_gamma((value - min_chan_val_) / (max_chan_val_ - min_chan_val_));
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    interp_channel_t
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    unnormalise(interp_channel_t value)
    {
        return fast_inv_gamma(value) * (max_chan_val_ - min_chan_val_) + min_chan_val_;
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    float
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    gamma(float value)
    {
        if (gamma_ == 1.0)
        {
            return value;
        }
        else
        {
            return std::pow(value, gamma_);
//            return (value <= 0.04045) ? value / 12.92 : std::pow((value + 0.055) / 1.055, 2.4);
        }
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    float
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    inv_gamma(float value)
    {
        if (gamma_ == 1.0)
        {
            return value;
        }
        else
        {
            return std::pow(static_cast<float>(value), static_cast<float>(1.0 / gamma_));
//            return (value <= 0.0031309) ? 12.92 * value : 1.055 * std::pow(value, 1.0 / 2.4) - 0.055;
        }
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    float
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    fast_gamma(float value)
    {
        if (gamma_ == 1.0)
        {
            return value;
        }

        int idx = static_cast<int>(value * 100);
        if (idx < 0) return 0;
        if (idx > 100) return 1;
        float a = gam_val_a_[idx];
        float b = gam_val_b_[idx];
        return a * value + b;
    }

    template <typename interpolator_t, typename image_view_w_t, unsigned int oversampling>
    float
    ImageTransform<interpolator_t, image_view_w_t, oversampling>::
    fast_inv_gamma(float value)
    {
        if (gamma_ == 1.0)
        {
            return value;
        }

        int idx = static_cast<int>(value * 100);
        if (idx < 0) return 0;
        if (idx > 100) return 1;
        float a = inv_gam_val_a_[idx];
        float b = inv_gam_val_b_[idx];
        return a * value + b;
    }

} // namespace phtr
