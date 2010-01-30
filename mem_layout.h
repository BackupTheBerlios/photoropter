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

#ifndef __MEM_LAYOUT_H__
#define __MEM_LAYOUT_H__

#include "types.h"
#include "storage_type.h"

namespace phtr
{

    /**
    * \brief Template to describe the memory layout of
    * a given \ref Storage::type.
    * \details This template \em has to be
    * specialised for every supported type. In each specialisation, the following
    * static member functions have to be provided: step, r_offs, g_offs, b_offs.
    * See the existing specialisations for example code.
    */
    template <Storage::type T>
    struct MemLayout
    {
    }; // template struct MemLayout

    /**
    * \brief Specialisation of \ref MemLayout for \ref Storage::rgb_8_inter.
    */
    template <>
    struct MemLayout<Storage::rgb_8_inter>
    {

        /**
        * \brief Return the number of channels (e.g., 3).
        * \return The number of channels.
        */
        static size_t num_channels()
        {
            return 3;
        }

        /**
        * \brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
        * \return The step value.
        */
        static size_t step(coord_t, coord_t)
        {
            return 3;
        }

        /**
        * \brief Return the red channel offset (e.g., 0).
        * \return The red offset.
        */
        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        /**
        * \brief Return the green channel offset (e.g., 0).
        * \return The green offset.
        */
        static size_t g_offs(coord_t, coord_t)
        {
            return 1;
        }

        /**
        * \brief Return the blue channel offset (e.g., 0).
        * \return The blue offset.
        */
        static size_t b_offs(coord_t, coord_t)
        {
            return 2;
        }

    }; // template struct MemLayout<Storage::rgb_8_inter>

    /**
    * \brief Specialisation of \ref MemLayout for \ref Storage::rgb_16_inter.
    */
    template <>
    struct MemLayout<Storage::rgb_16_inter>
    {

        /**
        * \brief Return the number of channels (e.g., 3).
        * \return The number of channels.
        */
        static size_t num_channels()
        {
            return 3;
        }

        /**
        * \brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
        * \return The step value.
        */
        static size_t step(coord_t, coord_t)
        {
            return 3;
        }

        /**
        * \brief Return the red channel offset (e.g., 0).
        * \return The red offset.
        */
        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        /**
        * \brief Return the green channel offset (e.g., 0).
        * \return The green offset.
        */
        static size_t g_offs(coord_t, coord_t)
        {
            return 1;
        }

        /**
        * \brief Return the blue channel offset (e.g., 0).
        * \return The blue offset.
        */
        static size_t b_offs(coord_t, coord_t)
        {
            return 2;
        }

    }; // template struct MemLayout<Storage::rgb_16_inter>

    /**
    * \brief Specialisation of \ref MemLayout for \ref Storage::rgb_32_inter.
    */
    template <>
    struct MemLayout<Storage::rgb_32_inter>
    {

        /**
        * \brief Return the number of channels (e.g., 3).
        * \return The number of channels.
        */
        static size_t num_channels()
        {
            return 3;
        }

        /**
        * \brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
        * \return The step value.
        */
        static size_t step(coord_t, coord_t)
        {
            return 3;
        }

        /**
        * \brief Return the red channel offset (e.g., 0).
        * \return The red offset.
        */
        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        /**
        * \brief Return the green channel offset (e.g., 0).
        * \return The green offset.
        */
        static size_t g_offs(coord_t, coord_t)
        {
            return 1;
        }

        /**
        * \brief Return the blue channel offset (e.g., 0).
        * \return The blue offset.
        */
        static size_t b_offs(coord_t, coord_t)
        {
            return 2;
        }

    }; // template struct MemLayout<Storage::rgb_32_inter>

    /**
    * \brief Specialisation of \ref MemLayout for \ref Storage::rgb_8_planar.
    */
    template <>
    struct MemLayout<Storage::rgb_8_planar>
    {

        /**
        * \brief Return the number of channels (e.g., 3).
        * \return The number of channels.
        */
        static size_t num_channels()
        {
            return 3;
        }

        /**
        * \brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
        * \return The step value.
        */
        static size_t step(coord_t, coord_t)
        {
            return 1;
        }

        /**
        * \brief Return the red channel offset (e.g., 0).
        * \return The red offset.
        */
        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        /**
        * \brief Return the green channel offset (e.g., 0).
        * \return The green offset.
        */
        static size_t g_offs(coord_t width, coord_t height)
        {
            return width * height;
        }

        /**
        * \brief Return the blue channel offset (e.g., 0).
        * \return The blue offset.
        */
        static size_t b_offs(coord_t width, coord_t height)
        {
            return 2 * width * height;
        }

    }; // template struct MemLayout<Storage::rgb_8_planar>

    /**
    * \brief Specialisation of \ref MemLayout for \ref Storage::rgb_16_planar.
    */
    template <>
    struct MemLayout<Storage::rgb_16_planar>
    {

        /**
        * \brief Return the number of channels (e.g., 3).
        * \return The number of channels.
        */
        static size_t num_channels()
        {
            return 3;
        }

        /**
        * \brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
        * \return The step value.
        */
        static size_t step(coord_t, coord_t)
        {
            return 1;
        }

        /**
        * \brief Return the red channel offset (e.g., 0).
        * \return The red offset.
        */
        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        /**
        * \brief Return the green channel offset (e.g., 0).
        * \return The green offset.
        */
        static size_t g_offs(coord_t width, coord_t height)
        {
            return width * height;
        }

        /**
        * \brief Return the blue channel offset (e.g., 0).
        * \return The blue offset.
        */
        static size_t b_offs(coord_t width, coord_t height)
        {
            return 2 * width * height;
        }

    }; // template struct MemLayout<Storage::rgb_16_planar>

    /**
    * \brief Specialisation of \ref MemLayout for \ref Storage::rgb_32_planar.
    */
    template <>
    struct MemLayout<Storage::rgb_32_planar>
    {

        /**
        * \brief Return the number of channels (e.g., 3).
        * \return The number of channels.
        */
        static size_t num_channels()
        {
            return 3;
        }

        /**
        * \brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
        * \return The step value.
        */
        static size_t step(coord_t, coord_t)
        {
            return 1;
        }

        /**
        * \brief Return the red channel offset (e.g., 0).
        * \return The red offset.
        */
        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        /**
        * \brief Return the green channel offset (e.g., 0).
        * \return The green offset.
        */
        static size_t g_offs(coord_t width, coord_t height)
        {
            return width * height;
        }

        /**
        * \brief Return the blue channel offset (e.g., 0).
        * \return The blue offset.
        */
        static size_t b_offs(coord_t width, coord_t height)
        {
            return 2 * width * height;
        }

    }; // template struct MemLayout<Storage::rgb_32_planar>

} // namespace phtr

#endif // __MEM_LAYOUT_H__
