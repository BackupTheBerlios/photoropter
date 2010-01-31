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
    * \brief Class to facilitate image interpolation.
    * \details The image is represented using floating-point coordinates ranging from
    *  -0.5 to 0.5. (0.0, 0.0) represents the image's center, (-0.5,-0.5) the upper left corner.
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
    * \brief Class to facilitate image interpolation.
    * \details The image is represented using floating-point coordinates ranging from
    *  -0.5 to 0.5. (0.0, 0.0) represents the image's center, (-0.5,-0.5) the upper left corner.
    * \note This is the specialisation for 'nearest neighbor' interpolation.
    */
    template <typename view_t>
    class ImageInterpolator<Interpolation::nearest_neighbour, view_t>
    {

        public:
            /**
            * \brief Constructor.
            */
            ImageInterpolator(view_t* image_view);

        public:
            /**
            * \brief Destructor.
            */
            virtual ~ImageInterpolator();

        public:
            /**
            * \brief Get the value of the 'red' channel at the given coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            channel_t get_px_val_r(interp_coord_t x, interp_coord_t y);

        private:
            /**
            * \brief Pointer to the internal image view instance that is used
            * for image access.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            view_t* image_view_;

        private:
            /**
            * \brief Interal scaling factor for the horizontal axis.
            */
            channel_t scale_x_;

        private:
            /**
            * \brief Interal scaling factor for the vertical axis.
            */
            channel_t scale_y_;

    }; // class ImageInterpolator

} // namespace phtr

#include "image_interpolator.tpl.h"

#endif // __IMAGE_INTERPOLATOR_H__
