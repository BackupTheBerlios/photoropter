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
    get_px_val_r
    (interp_coord_t x, interp_coord_t y)
    {
        return get_px_val(Channel::red, x, y);
    }

    template <typename view_t>
    interp_channel_t
    InterpolatorNN<view_t>::
    get_px_val_g
    (interp_coord_t x, interp_coord_t y)
    {
        return get_px_val(Channel::green, x, y);
    }

    template <typename view_t>
    interp_channel_t
    InterpolatorNN<view_t>::
    get_px_val_b
    (interp_coord_t x, interp_coord_t y)
    {
        return get_px_val(Channel::blue, x, y);
    }

    template <typename view_t>
    interp_channel_t
    InterpolatorNN<view_t>::
    get_px_val
    (Channel::type chan, interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + this->aspect_ratio_) * this->scale_x_;
        interp_coord_t y_scaled = (y + 1.0) * this->scale_y_;

        if ((x_scaled < 0) or(x_scaled > this->width_)
                or(y_scaled < 0) or(y_scaled > this->height_))
        {
            return this->null_val_;
        }

        return this->image_view_.get_px_val(chan, x_scaled + 0.5, y_scaled + 0.5);
    }

}
