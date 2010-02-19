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

#include "interpolator_nn.h"

namespace phtr
{

    template <typename view_t>
    InterpolatorNN<view_t>::InterpolatorNN
    (const view_t& image_view)
            : InterpolatorBase<view_t>(image_view)
    {
        //NIL
    }

    template <typename view_t>
    InterpolatorNN<view_t>::InterpolatorNN
    (const view_t& image_view, interp_coord_t aspect_ratio)
            : InterpolatorBase<view_t>(image_view, aspect_ratio)
    {
        //NIL
    }

    template <typename view_t>
    interp_channel_t
    InterpolatorNN<view_t>::
    get_px_val
    (Channel::type chan, interp_coord_t x, interp_coord_t y) const
    {
        interp_coord_t x_scaled = (x + this->aspect_ratio_) * this->scale_x_;
        interp_coord_t y_scaled = (y + 1.0) * this->scale_y_;

        if ((x_scaled < 0) or(x_scaled > this->width_)
                or(y_scaled < 0) or(y_scaled > this->height_))
        {
            return this->null_val_;
        }

        return this->image_view_.get_px_val(chan,
                                            static_cast<coord_t>(x_scaled + 0.5),
                                            static_cast<coord_t>(y_scaled + 0.5));
    }

    template <typename view_t> template <typename coord_tuple_t>
    typename coord_tuple_t::channel_order_t::colour_tuple_t
    InterpolatorNN<view_t>::
    get_px_vals(const coord_tuple_t& coords) const
    {
        typedef typename coord_tuple_t::channel_order_t::colour_tuple_t colour_tuple_t;

        colour_tuple_t ret;

        for (size_t i = 0; i < colour_tuple_t::num_vals; ++i)
        {
            ret.value[i] = get_px_val(coord_tuple_t::channel_order_t::channel_type[i], coords.x[i], coords.y[i]);
        }

        return ret;
    }

}
