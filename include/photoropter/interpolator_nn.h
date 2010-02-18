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

#ifndef __PHTR_INTERPOLATOR_NN_H__
#define __PHTR_INTERPOLATOR_NN_H__

#include <photoropter/coord_tuple.h>
#include <photoropter/colour_tuple.h>
#include <photoropter/interpolator_base.h>

namespace phtr
{

    /**
    * @brief Class template to facilitate 'nearest neighbor' image interpolation.
    * @details The image is represented using floating-point coordinates ranging from
    * -1.0 to 1.0 on the y axis. (0.0, 0.0) represents the image's centre, (-aspect,-1.0)
    * the upper left corner.
    * @param view_t  The image view that is used for reading data.
    */
    template <typename view_t>
    class InterpolatorNN : public InterpolatorBase<view_t>
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
            InterpolatorNN(const view_t& image_view);

        public:
            /**
            * @brief Constructor.
            * @param[in] image_view   The image view which will be used for reading image data.
            * @param[in] aspect_ratio The aspect ratio of the image.
            */
            InterpolatorNN(const view_t& image_view, interp_coord_t aspect_ratio);

        public:
            /**
            * @brief Get the value of the  given channel at the given coordinates.
            * @param chan The channel.
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
            inline mem::ColourTupleRGB get_px_vals(const mem::CoordTupleRGB& coords) const;

    }; // class InterpolatorNN<...>

} // namespace phtr

#include "interpolator_nn.tpl.h"

#endif // __PHTR_INTERPOLATOR_NN_H__
