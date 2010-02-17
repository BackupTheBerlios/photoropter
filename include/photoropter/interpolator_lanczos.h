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

#ifndef __PHTR_INTERPOLATOR_LANCZOS_H__
#define __PHTR_INTERPOLATOR_LANCZOS_H__

#include <cmath>
#include <vector>

#include <photoropter/interpolator_base.h>

namespace phtr
{

    /**
    * @brief Class template to facilitate Lanczos image interpolation.
    * @details The image is represented using floating-point coordinates ranging from
    * -1.0 to 1.0 on the y axis. (0.0, 0.0) represents the image's centre, (-aspect,-1.0)
    * the upper left corner.
    * @details This class implements a reconstructing Lanczos filter, not a classical lowpass.
    * The (one-dimensional) interpolation kernel in this case is the product of two sinc
    * functions: @f[
    * R(x)=\frac{\sin(\pi{}x)}{\pi{}x}\frac{\sin(\pi{}x/N)}{\pi{}x/N}
    * @f] where N=1,2,... marks the support of the kernel function. The kernel approximates
    * the 'ideal' sinc kernel for large N, while for smaller values the sharpness of the result
    * decreases, thus reducing ringing artefacts. N=2 and N=3 are the most common values which
    * represent a sensible compromise between sharpness, artefacts and computational complexity.
    * In two dimensions, the reconstruction/interpolation kernel function is simply the
    * product of two separate functions R(x) and R(y) (which is a bit different from the 'full' 2D
    * Lanczos lowpass).
    * @param view_t  The image view that is used for reading data.
    */
    template <typename view_t>
    class InterpolatorLanczos : public InterpolatorBase<view_t>
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
            InterpolatorLanczos(const view_t& image_view);

        public:
            /**
            * @brief Constructor.
            * @param[in] image_view   The image view which will be used for reading image data.
            * @param[in] aspect_ratio The aspect ratio of the image.
            */
            InterpolatorLanczos(const view_t& image_view, interp_coord_t aspect_ratio);

        public:
            /**
            * @brief Get the value of the 'red' channel at the given coordinates.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The channel value.
            */
            interp_channel_t get_px_val_r(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * @brief Get the value of the 'green' channel at the given coordinates.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The channel value.
            */
            interp_channel_t get_px_val_g(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * @brief Get the value of the 'blue' channel at the given coordinates.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The channel value.
            */
            interp_channel_t get_px_val_b(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * @brief Get the value of the  given channel at the given coordinates.
            * @param[in] chan The channel.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The channel value.
            */
            inline interp_channel_t get_px_val(Channel::type chan, interp_coord_t x, interp_coord_t y);

            /* ****************************************
             * internals
             * **************************************** */

        private:
            void precalc_kernel();

        private:
            double sinc(double x);

        private:
            const unsigned int support_;

        private:
            const unsigned int resolution_;

        private:
            std::vector<double> kernel_;

    }; // class InterpolatorLanczos<...>

} // namespace phtr

#include "interpolator_lanczos.tpl.h"

#endif // __PHTR_INTERPOLATOR_LANCZOS_H__
