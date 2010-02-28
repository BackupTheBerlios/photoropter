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

#ifndef PHTR_INTERPOLATOR_BASE_H__
#define PHTR_INTERPOLATOR_BASE_H__

#include <photoropter/types.h>

namespace phtr
{

    /**
    * @brief Image interpolation base class.
    * @details This stub (among other things) deals with the image's aspect ratio and
    * contains the image view reference. It is not supposed to be used directly.
    * @param view_T The image view that is used for reading data.
    */
    template <typename view_T>
    class InterpolatorBase
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief The type of the image view used.
            */
            typedef view_T image_view_t;

        public:
            /**
            * @brief Return the aspect ratio of the image.
            * @return The aspect ratio.
            */
            interp_coord_t aspect_ratio() const;

            /* ****************************************
             * internals
             * **************************************** */

            ///@cond PROTECTED
        protected:
            /**
            * @brief Constructor.
            * @note The aspect ratio will be calculated from width and height of the input
            * image, i.e. square pixels are assumed.
            * @param[in] image_view The image view which will be used for reading image data.
            */
            InterpolatorBase(const view_T& image_view);

        protected:
            /**
            * @brief Constructor.
            * @param[in] image_view   The image view which will be used for reading image data.
            * @param[in] aspect_ratio The aspect ratio of the image.
            */
            InterpolatorBase(const view_T& image_view, interp_coord_t aspect_ratio);

        protected:
            /**
            * @brief Pointer to the internal image view instance that is used
            * for image access.
            */
            const view_T& image_view_;

        protected:
            /**
            * @brief The image width.
            */
            const coord_t width_;

        protected:
            /**
            * @brief The image height.
            */
            const coord_t height_;

        protected:
            /**
            * @brief The value to return for areas outside the image.
            */
            const interp_channel_t null_val_;

        protected:
            /**
            * @brief The aspect ratio of the image.
            */
            const interp_coord_t aspect_ratio_;

        protected:
            /**
            * @brief Interal scaling factor for the horizontal axis.
            */
            const interp_channel_t scale_x_;

        protected:
            /**
            * @brief Interal scaling factor for the vertical axis.
            */
            const interp_channel_t scale_y_;
            ///@endcond

    }; // template class InterpolatorBase<...>

} // namespace phtr

#include <photoropter/interpolator_base.tpl.h>

#endif // PHTR_INTERPOLATOR_BASE_H__
