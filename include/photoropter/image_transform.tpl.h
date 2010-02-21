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

    template <typename interpolator_T, typename image_view_w_T>
    ImageTransform<interpolator_T, image_view_w_T>::
    ImageTransform
    (const typename ImageTransform::image_view_r_t& image_view_r, image_view_w_T& image_view_w)
            : interpolator_(image_view_r),
            image_view_w_(image_view_w),
            oversampling_(1),
            outp_img_width_(image_view_w.width()),
            outp_img_height_(image_view_w.height()),
            storage_info_(outp_img_width_, outp_img_height_),
            min_chan_val_(static_cast<interp_channel_t>(storage_info_.min_val)),
            max_chan_val_(static_cast<interp_channel_t>(storage_info_.max_val)),
            do_gamma_(true),
            do_inv_gamma_(true),
            gam_point_new_num_(1023),
            gam_point_cur_num_(0)
    {
        // set default gamma to sRGB
        set_gamma(gamma::GammaSRGB());
    }

    template <typename interpolator_T, typename image_view_w_T>
    void
    ImageTransform<interpolator_T, image_view_w_T>::
    do_transform()
    {
        // oversampling parameters
        const interp_coord_t sampling_fact = static_cast<interp_coord_t>(oversampling_);
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
            typename image_view_w_T::iter_t iter(image_view_w_.get_iter(i0, j));

            for (i = i0; i < i_limit; ++i) // pixel loop
            {
                // current pixel position
                interp_coord_t cur_pixel_x(i);
                interp_coord_t cur_pixel_y(j);

                /* scaled coordinates (in the interpolator coordinates system) */
                interp_coord_t dst_x(0);
                interp_coord_t dst_y(0);

                // coordinates transformed to source image
                coord_tuple_t src_coords;

                // channel value tuple (sum over oversampling steps)
                colour_tuple_t value_sum;
                value_sum.clear();

                // channel factors
                colour_tuple_t factors;

                // prepare (over-)sampling loop
                interp_coord_t cur_samp_x(0);
                interp_coord_t ini_samp_x(cur_pixel_x - 0.5 + (1.0 / (2 * sampling_fact)));
                interp_coord_t cur_samp_y(cur_pixel_y - 0.5 + (1.0 / (2 * sampling_fact)));
                unsigned int u(0);
                unsigned int v(0);

                for (v = 0; v < oversampling_; ++v)
                {
                    cur_samp_x = ini_samp_x;

                    for (u = 0; u < oversampling_; ++u)
                    {
                        // get scaled coordinates (in the interpolator coordinates system)
                        dst_x = ((cur_samp_x + p_offs_x) * scale_x) - aspect_ratio;
                        dst_y = ((cur_samp_y + p_offs_y) * scale_y) - 1.0;

                        // get coordinates transformed to source image
                        geom_queue_.get_src_coords(dst_x, dst_y, src_coords);

                        // get channel values and correction factors
                        colour_queue_.get_correction_factors(src_coords, factors);

                        value_sum += normalise(interpolator_.get_px_vals(src_coords)) * factors;

                        cur_samp_x += sampling_step_x;
                    } // (inner) oversampling loop

                    cur_samp_y += sampling_step_y;
                } // (outer) oversampling loop

                // scale channel values (due to oversampling)
                value_sum *= channel_scaling;

                // write channel values
                iter.write_px_vals(unnormalise(value_sum));

                // increment iterator position
                iter.inc_x();

            } // column loop

        } // line loop

    } //  ImageTransform<...>::do_transform()

    template <typename interpolator_T, typename image_view_w_T>
    GeomCorrectionQueue&
    ImageTransform<interpolator_T, image_view_w_T>::
    geom_queue()
    {
        return geom_queue_;
    }

    template <typename interpolator_T, typename image_view_w_T>
    ColourCorrectionQueue&
    ImageTransform<interpolator_T, image_view_w_T>::
    colour_queue()
    {
        return colour_queue_;
    }

    template <typename interpolator_T, typename image_view_w_T>
    void
    ImageTransform<interpolator_T, image_view_w_T>::
    set_gamma(const gamma::IGammaFunc& gam_func)
    {
        set_gamma(gam_func, gam_func);
    }

    template <typename interpolator_T, typename image_view_w_T>
    void
    ImageTransform<interpolator_T, image_view_w_T>::
    set_gamma(const gamma::IGammaFunc& gam_func, const gamma::IGammaFunc& inv_gam_func)
    {
        // prepare gamma lookup tables
        gam_val_a_.resize(gam_point_new_num_);
        gam_val_b_.resize(gam_point_new_num_);
        inv_gam_val_a_.resize(gam_point_new_num_);
        inv_gam_val_b_.resize(gam_point_new_num_);

        gam_point_cur_num_ = gam_point_new_num_;

        // fill tables
        for (unsigned int i = 0; i < gam_point_cur_num_; ++i)
        {
            double v1 = static_cast<double>(i) / (static_cast<double>(gam_point_new_num_) - 1.0);
            double v2 = static_cast<double>(i + 1) / (static_cast<double>(gam_point_new_num_) - 1.0);

            double g1 = gam_func.gamma(v1);
            double g2 = gam_func.gamma(v2);

            // determine slope
            double a = (g2 - g1) / (v2 - v1);

            gam_val_a_[i] = a;
            gam_val_b_[i] = g1 - a * v1;

            double ig1 = inv_gam_func.inv_gamma(v1);
            double ig2 = inv_gam_func.inv_gamma(v2);

            // determine slope
            double ia = (ig2 - ig1) / (v2 - v1);

            inv_gam_val_a_[i] = ia;
            inv_gam_val_b_[i] = ig1 - ia * v1;
        }

    }

    template <typename interpolator_T, typename image_view_w_T>
    void
    ImageTransform<interpolator_T, image_view_w_T>::
    set_gamma_precision(unsigned int num)
    {
        assert(gam_point_new_num_ >= 2);
        gam_point_new_num_ = num;
    }

    template <typename interpolator_T, typename image_view_w_T>
    void
    ImageTransform<interpolator_T, image_view_w_T>::
    enable_gamma(bool do_enable)
    {
        do_gamma_ = do_inv_gamma_ = do_enable;
    }

    template <typename interpolator_T, typename image_view_w_T>
    void
    ImageTransform<interpolator_T, image_view_w_T>::
    set_sampling_fact(unsigned int fact)
    {
        assert(fact > 0);
        oversampling_ = fact;
    }

    template <typename interpolator_T, typename image_view_w_T>
    interpolator_T&
    ImageTransform<interpolator_T, image_view_w_T>::
    interpolator()
    {
        return interpolator_;
    }


    template <typename interpolator_T, typename image_view_w_T>
    interp_channel_t
    ImageTransform<interpolator_T, image_view_w_T>::
    clip_val(const interp_channel_t& val) const
    {
        interp_channel_t ret(val);

        if (ret > 1.0)
        {
            ret = 1.0;
        }
        else if (ret < 0.0)
        {
            ret = 0.0;
        }

        return ret;
    }

    template <typename interpolator_T, typename image_view_w_T>
    interp_channel_t
    ImageTransform<interpolator_T, image_view_w_T>::
    normalise(interp_channel_t value) const
    {
        return static_cast<interp_channel_t>(
                   gamma((value - min_chan_val_) / (max_chan_val_ - min_chan_val_)));
    }

    template <typename interpolator_T, typename image_view_w_T> template <typename colour_tuple_T>
    colour_tuple_T
    ImageTransform<interpolator_T, image_view_w_T>::
    normalise(const colour_tuple_T& values) const
    {
        colour_tuple_T ret;

        for (size_t i = 0; i < colour_tuple_T::num_vals; ++i)
        {
            ret.value[i] = normalise(values.value[i]);
        }

        return ret;
    }

    template <typename interpolator_T, typename image_view_w_T>
    interp_channel_t
    ImageTransform<interpolator_T, image_view_w_T>::
    unnormalise(interp_channel_t value) const
    {
        return static_cast<interp_channel_t>(clip_val(inv_gamma(value)))
               * (max_chan_val_ - min_chan_val_) + min_chan_val_;
    }

    template <typename interpolator_T, typename image_view_w_T> template <typename colour_tuple_T>
    colour_tuple_T
    ImageTransform<interpolator_T, image_view_w_T>::
    unnormalise(const colour_tuple_T& values) const
    {
        colour_tuple_T ret;

        for (size_t i = 0; i < colour_tuple_T::num_vals; ++i)
        {
            ret.value[i] = unnormalise(values.value[i]);
        }

        return ret;
    }

    template <typename interpolator_T, typename image_view_w_T>
    double
    ImageTransform<interpolator_T, image_view_w_T>::
    gamma(double value) const
    {

        if (!do_gamma_)
        {
            return value;
        }

        if (value <= 0.0)
        {
            return 0.0;
        }

        unsigned int idx = static_cast<unsigned int>(value * (gam_point_cur_num_ - 1));

        if (idx >= gam_point_cur_num_)
        {
            return 1.0;
        }
        else
        {
            double a = gam_val_a_[idx];
            double b = gam_val_b_[idx];

            return a * value + b;
        }

    }

    template <typename interpolator_T, typename image_view_w_T>
    double
    ImageTransform<interpolator_T, image_view_w_T>::
    inv_gamma(double value) const
    {

        if (!do_inv_gamma_)
        {
            return value;
        }

        if (value <= 0.0)
        {
            return 0.0;
        }

        unsigned int idx = static_cast<unsigned int>(value * (gam_point_cur_num_ - 1));

        if (idx >= gam_point_cur_num_)
        {
            return 1.0;
        }
        else
        {
            double a = inv_gam_val_a_[idx];
            double b = inv_gam_val_b_[idx];

            return a * value + b;
        }

    }

} // namespace phtr
