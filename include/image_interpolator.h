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

#ifndef __IMAGE_INTERPOLATOR_H__
#define __IMAGE_INTERPOLATOR_H__

#include "mem_image_view_r.h"
#include "types.h"

#include <cmath>
#include <memory>

namespace phtr
{

    /**
    * \brief Struct describing interpolation types.
    */
    struct Interpolation
    {

        /**
        * \brief The enum holding the actual values.
        */
        enum type
        {
            /**
            * \brief 'Nearest neighbour' interpolation.
            */
            nearest_neighbour = 0,
            /**
            * \brief Bilinear interpolation.
            */
            bilinear,
            /**
            * \brief Lanczos interpolation.
            */
            lanczos
        };

    }; // struct Interpolation

} // namespace phtr

namespace phtr
{

    /**
    * \brief Class template to facilitate image interpolation.
    * \details The image is represented using floating-point coordinates ranging from
    *  -0.5 to 0.5. (0.0, 0.0) represents the image's center, (-0.5,-0.5) the upper left corner.
    * \note This (unspecialised) version does not provide any functionality. Have a look at
    * e.g., \ref ImageInterpolator<Interpolation::nearest_neighbour, view_t>.
    */
    template <Interpolation::type inter_t, typename view_t>
    class ImageInterpolator
    {
            // provoke a compile-time error whenever this unspecialised version is used
            struct must_be_specialised_t;
            const size_t must_be_specialised;
            ImageInterpolator() : must_be_specialised(sizeof(must_be_specialised_t)) {}
    };

    /**
    * \brief Class template to facilitate image interpolation.
    * \details The image is represented using floating-point coordinates ranging from
    *  -0.5 to 0.5. (0.0, 0.0) represents the image's center, (-0.5,-0.5) the upper left corner.
    * \note This is the specialisation for 'nearest neighbor' interpolation.
    */
    template <typename view_t>
    class ImageInterpolator<Interpolation::nearest_neighbour, view_t>
    {
            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief The type of the image view used.
            */
            typedef view_t image_view_t;

        public:
            /**
            * \brief Constructor.
            */
            ImageInterpolator(const view_t& image_view);

        public:
            /**
            * \brief Destructor.
            */
            ~ImageInterpolator();

        public:
            /**
            * \brief Get the value of the 'red' channel at the given coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            interp_channel_t get_px_val_r(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * \brief Get the value of the 'green' channel at the given coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            interp_channel_t get_px_val_g(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * \brief Get the value of the 'blue' channel at the given coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            interp_channel_t get_px_val_b(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * \brief Get the value of the  given channel at the given coordinates.
            * \param chan The channel.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            inline interp_channel_t get_px_val(Channel::type chan, interp_coord_t x, interp_coord_t y);

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief Pointer to the internal image view instance that is used
            * for image access.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            const view_t& image_view_;

        private:
            /**
            * \brief Interal scaling factor for the horizontal axis.
            */
            interp_channel_t scale_x_;

        private:
            /**
            * \brief Interal scaling factor for the vertical axis.
            */
            interp_channel_t scale_y_;

        private:
            /**
            * \brief The image width.
            */
            coord_t width_;

        private:
            /**
            * \brief The image height.
            */
            coord_t height_;

        private:
            /**
            * \brief The value to return for areas outside the image.
            */
            interp_channel_t null_val_;

    }; // class ImageInterpolator<Interpolation::nearest_neighbour, ...>

    /**
    * \brief Class template to facilitate image interpolation.
    * \details The image is represented using floating-point coordinates ranging from
    *  -0.5 to 0.5. (0.0, 0.0) represents the image's center, (-0.5,-0.5) the upper left corner.
    * \note This is the specialisation for bilinear interpolation.
    */
    template <typename view_t>
    class ImageInterpolator<Interpolation::bilinear, view_t>
    {
            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief The type of the image view used.
            */
            typedef view_t image_view_t;

        public:
            /**
            * \brief Constructor.
            */
            ImageInterpolator(const view_t& image_view);

        public:
            /**
            * \brief Destructor.
            */
            ~ImageInterpolator();

        public:
            /**
            * \brief Get the value of the 'red' channel at the given coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            interp_channel_t get_px_val_r(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * \brief Get the value of the 'green' channel at the given coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            interp_channel_t get_px_val_g(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * \brief Get the value of the 'blue' channel at the given coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            interp_channel_t get_px_val_b(interp_coord_t x, interp_coord_t y);

        public:
            /**
            * \brief Get the value of the  given channel at the given coordinates.
            * \param chan The channel.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            inline interp_channel_t get_px_val(Channel::type chan, interp_coord_t x, interp_coord_t y);

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief Pointer to the internal image view instance that is used
            * for image access.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            const view_t& image_view_;

        private:
            /**
            * \brief Interal scaling factor for the horizontal axis.
            */
            interp_channel_t scale_x_;

        private:
            /**
            * \brief Interal scaling factor for the vertical axis.
            */
            interp_channel_t scale_y_;

        private:
            /**
            * \brief The image width.
            */
            coord_t width_;

        private:
            /**
            * \brief The image height.
            */
            coord_t height_;

        private:
            /**
            * \brief The value to return for areas outside the image.
            */
            interp_channel_t null_val_;

    }; // class ImageInterpolator<Interpolation::bilinear, ...>

} // namespace phtr

#include "image_interpolator.tpl.h"

#endif // __IMAGE_INTERPOLATOR_H__
