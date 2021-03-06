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

#ifndef PHTR_INTERPOLATOR_BILINEAR_H__
#define PHTR_INTERPOLATOR_BILINEAR_H__

#include <cmath>
#include <cassert>

#include <photoropter/mem/coord_tuple.h>
#include <photoropter/mem/colour_tuple.h>
#include <photoropter/interpolator/interpolator_base.h>

namespace phtr
{

    /**
    * @brief Class template to facilitate bilinear image interpolation.
    * @details The image is represented using floating-point coordinates ranging from
    * -1.0 to 1.0 on the y axis. (0.0, 0.0) represents the image's centre, (-aspect,-1.0)
    * the upper left corner.
    * @param view_T  The image view that is used for reading data.
    */
    template <typename view_T>
    class InterpolatorBilinear : public InterpolatorBase<view_T>
    {
            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief Constructor.
            * @note The aspect ratio will be calculated from width and height of the input
            * image, i.e. square pixels are assumed.
            * @param[in] image_view The image view which will be used for reading image data.
            */
            InterpolatorBilinear(const view_T& image_view);

        public:
            /**
            * @brief Constructor.
            * @param[in] image_view   The image view which will be used for reading image data.
            * @param[in] aspect_ratio The aspect ratio of the image.
            */
            InterpolatorBilinear(const view_T& image_view, interp_coord_t aspect_ratio);

        public:
            /**
            * @brief Get the value of the  given channel at the given coordinates.
            * @param[in] chan The channel.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The channel value.
            */
            inline interp_channel_t get_px_val(Channel::type chan, interp_coord_t x, interp_coord_t y) const;

        public:
            /**
             * @brief Get the channel values at the given positions.
             * @param[in] coords The coordinates tuple.
             * @return The channel values.
             */
            template <typename coord_tuple_T>
            inline typename coord_tuple_T::channel_order_t::colour_tuple_t get_px_vals(const coord_tuple_T& coords) const;


    }; // class InterpolatorBilinear<...>

} // namespace phtr

#include <photoropter/interpolator/interpolator_bilinear.tpl.h>

#endif // PHTR_INTERPOLATOR_BILINEAR_H__
