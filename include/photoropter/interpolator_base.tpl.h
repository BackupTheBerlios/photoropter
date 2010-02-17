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

    /* ****************************************
     * base
     * **************************************** */

    template <typename view_t>
    InterpolatorBase<view_t>::InterpolatorBase
    (const view_t& image_view)
            : image_view_(image_view),
            width_(image_view_.width()),
            height_(image_view_.height()),
            null_val_(0),
            aspect_ratio_(image_view_.aspect_ratio()),
            scale_x_((static_cast<interp_coord_t>(image_view_.width()) - 1.0) / (2.0 * aspect_ratio_)),
            scale_y_((static_cast<interp_coord_t>(image_view_.height()) - 1.0) / 2.0)
    {
        //NIL
    }

    template <typename view_t>
    InterpolatorBase<view_t>::InterpolatorBase
    (const view_t& image_view, interp_coord_t aspect_ratio)
            : image_view_(image_view),
            width_(image_view_.width()),
            height_(image_view_.height()),
            null_val_(0),
            aspect_ratio_(aspect_ratio),
            scale_x_((static_cast<interp_coord_t>(image_view_.width()) - 1.0) / (2.0 * aspect_ratio_)),
            scale_y_((static_cast<interp_coord_t>(image_view_.height()) - 1.0) / 2.0)
    {
        //NIL
    }

    template <typename view_t>
    interp_coord_t InterpolatorBase<view_t>::aspect_ratio() const
    {
        return aspect_ratio_;
    }

} // namespace phtr
