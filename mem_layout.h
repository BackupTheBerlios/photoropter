#ifndef __MEM_LAYOUT_H__
#define __MEM_LAYOUT_H__

#include "types.h"
#include "storagetypes.h"

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

        static size_t step(coord_t, coord_t)
        {
            return 3;
        }

        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        static size_t g_offs(coord_t, coord_t)
        {
            return 1;
        }

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

        static size_t step(coord_t, coord_t)
        {
            return 3;
        }

        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        static size_t g_offs(coord_t, coord_t)
        {
            return 1;
        }

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

        static size_t step(coord_t, coord_t)
        {
            return 3;
        }

        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        static size_t g_offs(coord_t, coord_t)
        {
            return 1;
        }

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

        static size_t step(coord_t, coord_t)
        {
            return 1;
        }

        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        static size_t g_offs(coord_t width, coord_t height)
        {
            return width * height;
        }

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

        static size_t step(coord_t, coord_t)
        {
            return 1;
        }

        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        static size_t g_offs(coord_t width, coord_t height)
        {
            return width * height;
        }

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

        static size_t step(coord_t, coord_t)
        {
            return 1;
        }

        static size_t r_offs(coord_t, coord_t)
        {
            return 0;
        }

        static size_t g_offs(coord_t width, coord_t height)
        {
            return width * height;
        }

        static size_t b_offs(coord_t width, coord_t height)
        {
            return 2 * width * height;
        }

    }; // template struct MemLayout<Storage::rgb_32_planar>

} // namespace phtr

#endif // __MEM_LAYOUT_H__
