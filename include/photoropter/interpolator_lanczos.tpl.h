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

    template <typename view_t>
    InterpolatorLanczos<view_t>::InterpolatorLanczos
    (const view_t& image_view)
            : InterpolatorBase<view_t>(image_view),
            support_(2),
            resolution_(1024)
    {
        precalc_kernel();
    }

    template <typename view_t>
    InterpolatorLanczos<view_t>::InterpolatorLanczos
    (const view_t& image_view, interp_coord_t aspect_ratio)
            : InterpolatorBase<view_t>(image_view, aspect_ratio)
    {
    }

    template <typename view_t>
    interp_channel_t
    InterpolatorLanczos<view_t>::
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

        long x_left = x0 - support_ + 1;
        long x_right = x0 + support_ + 1;
        long y_top = y0 - support_ + 1;
        long y_bottom = y0 + support_ + 1;

        if (x_left < 0) x_left = 0;
        if (x_right > static_cast<long>(this->width_)) x_right = static_cast<long>(this->width_);
        if (y_top < 0) y_top = 0;
        if (y_bottom > static_cast<long>(this->height_)) y_bottom = static_cast<long>(this->height_);

        interp_channel_t cur_val(0);
        interp_channel_t sum_val(0);
        double sum_fact(0);
        double fact(0);

        long i(0);
        long j(0);
        for (long y = y_top; y < y_bottom; ++y)
        {
            j = y0 - y;
            typename view_t::iter_t iter(this->image_view_.get_iter(x_left, y));

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

    template <typename view_t>
    mem::ColourTupleRGB
    InterpolatorLanczos<view_t>::
    get_px_vals(const mem::CoordTupleRGB& coords) const
    {
        mem::ColourTupleRGB ret;

        ret.val_r = get_px_val(Channel::red,   coords.x_r, coords.y_r);
        ret.val_g = get_px_val(Channel::green, coords.x_g, coords.y_g);
        ret.val_b = get_px_val(Channel::blue,  coords.x_b, coords.y_b);

        return ret;
    }

    template <typename view_t>
    void
    InterpolatorLanczos<view_t>::
    InterpolatorLanczos::precalc_kernel()
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

    template <typename view_t>
    double
    InterpolatorLanczos<view_t>::
    InterpolatorLanczos::sinc(double x)
    {
        if (x == 0.0)
        {
            return 1.0;
        }
        else
        {
            return std::sin(M_PI * x) / (M_PI * x);
        }
    }

} // namespace phtr
