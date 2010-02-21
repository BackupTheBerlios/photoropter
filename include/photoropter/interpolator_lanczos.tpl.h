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

    template <typename view_T>
    const double
    InterpolatorLanczos<view_T>::pi_ = 3.14159265358979323846;

    template <typename view_T>
    InterpolatorLanczos<view_T>::InterpolatorLanczos
    (const view_T& image_view)
            : InterpolatorBase<view_T>(image_view),
            support_(2),
            resolution_(1024)
    {
        precalc_kernel();
    }

    template <typename view_T>
    InterpolatorLanczos<view_T>::InterpolatorLanczos
    (const view_T& image_view, interp_coord_t aspect_ratio)
            : InterpolatorBase<view_T>(image_view, aspect_ratio)
    {
    }

    template <typename view_T>
    void
    InterpolatorLanczos<view_T>::set_support
    (unsigned int supp)
    {
        assert(supp > 0);

        support_ = supp;
        precalc_kernel();
    }

    template <typename view_T>
    void
    InterpolatorLanczos<view_T>::set_resolution
    (unsigned int res)
    {
        resolution_ = res;
        precalc_kernel();
    }

    template <typename view_T>
    interp_channel_t
    InterpolatorLanczos<view_T>::
    get_px_val
    (Channel::type chan, interp_coord_t x, interp_coord_t y) const
    {
        interp_coord_t x_scaled = (x + this->aspect_ratio_) * this->scale_x_;
        interp_coord_t y_scaled = (y + 1.0) * this->scale_y_;

        if ((x_scaled < 0) || (x_scaled > this->width_)
                || (y_scaled < 0) || (y_scaled > this->height_))
        {
            return this->null_val_;
        }

        coord_t xoffs = static_cast<coord_t>((x_scaled - std::floor(x_scaled)) * resolution_);
        coord_t yoffs = static_cast<coord_t>((y_scaled - std::floor(y_scaled)) * resolution_);

        long x0 = static_cast<coord_t>(x_scaled);
        long y0 = static_cast<coord_t>(y_scaled);

        // determine interpolation area
        long x_left = x0 - support_ + 1;
        long x_right = x0 + support_ + 1;
        long y_top = y0 - support_ + 1;
        long y_bottom = y0 + support_ + 1;

        // check boundaries
        if (x_left < 0)
        {
            x_left = 0;
        }
        if (x_right > static_cast<long>(this->width_))
        {
            x_right = static_cast<long>(this->width_);
        }
        if (y_top < 0)
        {
            y_top = 0;
        }
        if (y_bottom > static_cast<long>(this->height_))
        {
            y_bottom = static_cast<long>(this->height_);
        }

        interp_channel_t cur_val(0); // current channel value
        interp_channel_t sum_val(0); // sum of values so far
        double sum_fact(0); // sum of Lanczos weight factors (for normalisation)
        double fact(0); // current Lanczos weight factor
        typename view_T::iter_t iter(this->image_view_.get_iter(0, 0));

        long i(0);
        long j(0);
        for (long y = y_top; y < y_bottom; ++y)
        {
            j = y0 - y;
            iter.set_px_offs(this->image_view_.get_px_offs(x_left, y));

            for (long x = x_left; x < x_right; ++x)
            {
                i = x0 - x;
                cur_val = iter.get_px_val(chan);
                iter.inc_x();

                long x_idx = (i + support_) * resolution_ + xoffs;
                long y_idx = (j + support_) * resolution_ + yoffs;
                fact = kernel_[x_idx] * kernel_[y_idx];
                cur_val *= fact;

                sum_fact += fact;
                sum_val += cur_val;
            }
        }

        return sum_val / sum_fact;

    }

    template <typename view_T> template <typename coord_tuple_T>
    typename coord_tuple_T::channel_order_t::colour_tuple_t
    InterpolatorLanczos<view_T>::
    get_px_vals(const coord_tuple_T& coords) const
    {
        typedef typename coord_tuple_T::channel_order_t::colour_tuple_t colour_tuple_t;

        colour_tuple_t ret;

        for (size_t i = 0; i < colour_tuple_t::num_vals; ++i)
        {
            ret.value[i] = get_px_val(coord_tuple_T::channel_order_t::channel_type[i], coords.x[i], coords.y[i]);
        }

        return ret;
    }

    template <typename view_T>
    void
    InterpolatorLanczos<view_T>::
    precalc_kernel()
    {
        unsigned int num_val = 2 * resolution_ * support_ + 1;

        kernel_.resize(num_val, 0.0);
        buf_.resize((2 * support_ + 1) * (2 * support_ + 1));

        for (unsigned int i = 0; i < num_val; ++i)
        {
            double x = (static_cast<double>(support_ * i) / static_cast<double>(resolution_ * support_))
                       - static_cast<double>(support_);
            double y = sinc(x) * sinc(x / support_);

            kernel_[i] = y;
        }
    }

    template <typename view_T>
    double
    InterpolatorLanczos<view_T>::
    sinc(double x)
    {
        if (x == 0.0)
        {
            return 1.0;
        }
        else
        {
            return std::sin(pi_ * x) / (pi_ * x);
        }
    }

} // namespace phtr
