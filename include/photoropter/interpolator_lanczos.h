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

#include <photoropter/mem/coord_tuple.h>
#include <photoropter/mem/colour_tuple.h>
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
    * @param view_T  The image view that is used for reading data.
    */
    template <typename view_T>
    class InterpolatorLanczos : public InterpolatorBase<view_T>
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
            InterpolatorLanczos(const view_T& image_view);

        public:
            /**
            * @brief Constructor.
            * @param[in] image_view   The image view which will be used for reading image data.
            * @param[in] aspect_ratio The aspect ratio of the image.
            */
            InterpolatorLanczos(const view_T& image_view, interp_coord_t aspect_ratio);

        public:
            /**
             * @brief Set support size of the Lanzcos interpolation kernel.
             * @details The minimal legal value is 1; sensible choices range between
             * 1 and 3. The default value is 2.
             * @param[in] supp The new support size.
             */
            void set_support(unsigned int supp);

        public:
            /**
             * @brief Set resolution of the Lanzcos interpolation kernel.
             * @details The default value is 1024.
             * @param[in] res The new resolution.
             */
            void set_resolution(unsigned int res);

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

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
             * @brief Pre-compute the Lanczos kernel and allocate buffer structures.
             */
            void precalc_kernel();

        private:
            /**
             * @brief The sinc function.
             * @details @f[\frac{sin(\pi{}x)}{\pi{}x}@f]
             */
            double sinc(double x);

        private:
            /**
             * @brief The size of the interpolation kernel's support (i.e., commonly 2 or 3).
             */
            unsigned int support_;

        private:
            /**
             * @brief The interpolation resolution (samples per unit length, i.e. 1024).
             */
            unsigned int resolution_;

        private:
            /**
             * @brief The interpolation kernel buffer.
             */
            std::vector<double> kernel_;

        private:
            /**
             * @brief The pixel interpolation buffer.
             */
            std::vector<interp_channel_t> buf_;

        private:
            /**
             * @brief The numerical constant 'pi'.
             */
            static const double pi_;

    }; // class InterpolatorLanczos<...>

} // namespace phtr

#include "interpolator_lanczos.tpl.h"

#endif // __PHTR_INTERPOLATOR_LANCZOS_H__
