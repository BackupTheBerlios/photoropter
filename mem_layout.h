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
