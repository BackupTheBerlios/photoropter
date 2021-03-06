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

#ifndef PHTR_MEM_LAYOUT_H__
#define PHTR_MEM_LAYOUT_H__

#include <photoropter/types.h>
#include <photoropter/mem/channel_type.h>
#include <photoropter/mem/storage_type.h>

namespace phtr
{

    /**
    * @brief Memory layout and storage related stuff
    */
    namespace mem
    {

        // necessary forward declarations
        template <typename channel_order_T, size_t num_vals_T>
        struct CoordTuple;
        template <typename channel_order_T, size_t num_vals_T>
        struct ColourTuple;

        /**
         * @brief Struct describing the order of channels. Used as base by
         * specialisations of @ref MemLayout.
         * @note: This describes a (i.e., monochrome) single-channel structure.
         */
        struct ChannelOrderMono
        {

            /**
                * @brief The type of coordinate tuples (i.e., mem::CoordTupleRGB or mem::CoordTupleRGBA).
                */
            typedef CoordTuple<ChannelOrderMono, 1> coord_tuple_t;

            /**
             * @brief The type of colour tuples (i.e., mem::ColourTupleRGB or mem::ColourTupleRGBA).
             */
            typedef ColourTuple<ChannelOrderMono, 1> colour_tuple_t;

            /**
            * @brief Return the channel order for this layout type.
            * @param chan_type The channel type.
            * @return The index (i.e., 0).
            */
            static size_t get_channel_index(Channel::type chan_type);

            /**
             * @brief The channel types.
             */
            static const Channel::type channel_type[];

            /**
             * @brief The index of the red channel.
             */
            static const size_t idx_red;

            /**
             * @brief The index of the green channel.
             */
            static const size_t idx_green;

            /**
             * @brief The index of the blue channel.
             */
            static const size_t idx_blue;

            /**
             * @brief The index of the alpha channel.
             */
            static const size_t idx_alpha;

        };

        /**
         * @brief Struct describing the order of channels. Used as base by
         * specialisations of @ref MemLayout.
         * @note: This describes the 3-channel (RGB) case.
         */
        struct ChannelOrderRGB
        {

            /**
                * @brief The type of coordinate tuples (i.e., mem::CoordTupleRGB or mem::CoordTupleRGBA).
                */
            typedef CoordTuple<ChannelOrderRGB, 3> coord_tuple_t;

            /**
             * @brief The type of colour tuples (i.e., mem::ColourTupleRGB or mem::ColourTupleRGBA).
             */
            typedef ColourTuple<ChannelOrderRGB, 3> colour_tuple_t;

            /**
            * @brief Return the channel order for this layout type.
            * @param chan_type The channel type.
            * @return The index (i.e., 0-2).
            */
            static size_t get_channel_index(Channel::type chan_type);

            /**
             * @brief The channel types.
             */
            static const Channel::type channel_type[];

            /**
             * @brief The index of the red channel.
             */
            static const size_t idx_red;

            /**
             * @brief The index of the green channel.
             */
            static const size_t idx_green;

            /**
             * @brief The index of the blue channel.
             */
            static const size_t idx_blue;

            /**
             * @brief The index of the alpha channel.
             */
            static const size_t idx_alpha;

        };

        /**
         * @brief Struct describing the order of channels. Used as base by
         * specialisations of @ref MemLayout.
         * @note: This describes the 4-channel (RGBA) case.
         */
        struct ChannelOrderRGBA
        {

            /**
                * @brief The type of coordinate tuples (i.e., mem::CoordTupleRGB or mem::CoordTupleRGBA).
                */
            typedef CoordTuple<ChannelOrderRGBA, 4> coord_tuple_t;

            /**
             * @brief The type of colour tuples (i.e., mem::ColourTupleRGB or mem::ColourTupleRGBA).
             */
            typedef ColourTuple<ChannelOrderRGBA, 4> colour_tuple_t;

            /**
            * @brief Return the channel order for this layout type.
            * @param chan_type The channel type.
            * @return The index (i.e., 0-3).
            */
            static size_t get_channel_index(Channel::type chan_type);

            /**
             * @brief The channel types.
             */
            static const Channel::type channel_type[];

            /**
             * @brief The index of the red channel.
             */
            static const size_t idx_red;

            /**
             * @brief The index of the green channel.
             */
            static const size_t idx_green;

            /**
             * @brief The index of the blue channel.
             */
            static const size_t idx_blue;

            /**
             * @brief The index of the alpha channel.
             */
            static const size_t idx_alpha;

        };

        /**
        * @brief Struct describing a generic interleaved memory storage type. Used as base by
        * some specialisations of @ref MemLayout.
        */
        struct GenericInterleavedLayoutRGB
        {

            /**
            * @brief Return the number of channels (e.g., 3).
            * @details The number has to be at least 3 in order for RGB data to fit,
            * but can be larger (e.g. 4 for RGBA).
            * @note Additional channels are ignored by Photoropter.
            * @return The number of channels.
            */
            static size_t num_channels()
            {
                return 3;
            }

            /**
            * @brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
            * @return The step value.
            */
            static size_t step(coord_t, coord_t)
            {
                return 3;
            }

            /**
            * @brief Return the 'step' between lines (e.g., 3 * width for RGB interleaved)
            * @return The step value.
            */
            static size_t line_step(coord_t width, coord_t)
            {
                return 3 * width;
            }

            /**
            * @brief Return the red channel offset (e.g., 0).
            * @return The red offset.
            */
            static size_t r_offs(coord_t, coord_t)
            {
                return 0;
            }

            /**
            * @brief Return the green channel offset (e.g., 0).
            * @return The green offset.
            */
            static size_t g_offs(coord_t, coord_t)
            {
                return 1;
            }

            /**
            * @brief Return the blue channel offset (e.g., 0).
            * @return The blue offset.
            */
            static size_t b_offs(coord_t, coord_t)
            {
                return 2;
            }

            /**
            * @brief Return the alpha channel offset (e.g., 0 for non-alpha images).
            * @return The alpha offset.
            */
            static size_t a_offs(coord_t, coord_t)
            {
                return 0;
            }

        }; // struct GenericInterleavedLayoutRGB

        /**
        * @brief Struct describing a generic interleaved memory storage type. Used as base by
        * some specialisations of @ref MemLayout.
        */
        struct GenericInterleavedLayoutRGBA
        {

            /**
            * @brief Return the number of channels (e.g., 3).
            * @details The number has to be at least 3 in order for RGB data to fit,
            * but can be larger (e.g. 4 for RGBA).
            * @note Additional channels are ignored by Photoropter.
            * @return The number of channels.
            */
            static size_t num_channels()
            {
                return 4;
            }

            /**
            * @brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
            * @return The step value.
            */
            static size_t step(coord_t, coord_t)
            {
                return 4;
            }

            /**
            * @brief Return the 'step' between lines (e.g., 3 * width for RGB interleaved)
            * @return The step value.
            */
            static size_t line_step(coord_t width, coord_t)
            {
                return 4 * width;
            }

            /**
            * @brief Return the red channel offset (e.g., 0).
            * @return The red offset.
            */
            static size_t r_offs(coord_t, coord_t)
            {
                return 0;
            }

            /**
            * @brief Return the green channel offset (e.g., 0).
            * @return The green offset.
            */
            static size_t g_offs(coord_t, coord_t)
            {
                return 1;
            }

            /**
            * @brief Return the blue channel offset (e.g., 0).
            * @return The blue offset.
            */
            static size_t b_offs(coord_t, coord_t)
            {
                return 2;
            }

            /**
            * @brief Return the alpha channel offset (e.g., 0 for non-alpha images).
            * @return The alpha offset.
            */
            static size_t a_offs(coord_t, coord_t)
            {
                return 3;
            }

        }; // struct GenericInterleavedLayoutRGBA

        /**
        * @brief Struct describing a generic planar memory storage type. Used as base by
        * some specialisations of @ref MemLayout.
        */
        struct GenericPlanarLayoutRGB
        {

            /**
            * @brief Return the number of channels (e.g., 3).
            * @details The number has to be at least 3 in order for RGB data to fit,
            * but can be larger (e.g. 4 for RGBA).
            * @note Additional channels are ignored by Photoropter.
            * @return The number of channels.
            */
            static size_t num_channels()
            {
                return 3;
            }

            /**
            * @brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
            * @return The step value.
            */
            static size_t step(coord_t, coord_t)
            {
                return 1;
            }

            /**
            * @brief Return the 'step' between lines (e.g., 3 * width for RGB interleaved)
            * @return The step value.
            */
            static size_t line_step(coord_t width, coord_t)
            {
                return width;
            }

            /**
            * @brief Return the red channel offset (e.g., 0).
            * @return The red offset.
            */
            static size_t r_offs(coord_t, coord_t)
            {
                return 0;
            }

            /**
            * @brief Return the green channel offset (e.g., width * height).
            * @return The green offset.
            */
            static size_t g_offs(coord_t width, coord_t height)
            {
                return width * height;
            }

            /**
            * @brief Return the blue channel offset (e.g., 2 * width * height).
            * @return The blue offset.
            */
            static size_t b_offs(coord_t width, coord_t height)
            {
                return 2 * width * height;
            }

            /**
            * @brief Return the alpha channel offset (e.g., 3 * width * height, 0 for non-alpha images).
            * @return The alpha offset.
            */
            static size_t a_offs(coord_t, coord_t)
            {
                return 0;
            }

        }; // struct GenericPlanarLayoutRGB

        /**
        * @brief Struct describing a generic planar memory storage type. Used as base by
        * some specialisations of @ref MemLayout.
        */
        struct GenericPlanarLayoutRGBA
        {

            /**
            * @brief Return the number of channels (e.g., 3).
            * @details The number has to be at least 3 in order for RGB data to fit,
            * but can be larger (e.g. 4 for RGBA).
            * @note Additional channels are ignored by Photoropter.
            * @return The number of channels.
            */
            static size_t num_channels()
            {
                return 4;
            }

            /**
            * @brief Return the 'step' between pixels (e.g., 3 for RGB interleaved)
            * @return The step value.
            */
            static size_t step(coord_t, coord_t)
            {
                return 1;
            }

            /**
            * @brief Return the 'step' between lines (e.g., 3 * width for RGB interleaved)
            * @return The step value.
            */
            static size_t line_step(coord_t width, coord_t)
            {
                return width;
            }

            /**
            * @brief Return the red channel offset (e.g., 0).
            * @return The red offset.
            */
            static size_t r_offs(coord_t, coord_t)
            {
                return 0;
            }

            /**
            * @brief Return the green channel offset (e.g., width * height).
            * @return The green offset.
            */
            static size_t g_offs(coord_t width, coord_t height)
            {
                return width * height;
            }

            /**
            * @brief Return the blue channel offset (e.g., 2 * width * height).
            * @return The blue offset.
            */
            static size_t b_offs(coord_t width, coord_t height)
            {
                return 2 * width * height;
            }

            /**
            * @brief Return the alpha channel offset (e.g., 3 * width * height, 0 for non-alpha images).
            * @return The alpha offset.
            */
            static size_t a_offs(coord_t width, coord_t height)
            {
                return 3 * width * height;
            }

        }; // struct GenericPlanarLayoutRGBA

        /**
        * @brief Template to describe the memory layout of
        * a given @ref Storage::type.
        * @details This template @em has to be
        * specialised for every supported type. In each specialisation, the following
        * static member functions have to be provided: step, r_offs, g_offs, b_offs.
        * See the existing specialisations for example code.
        * @param storage_T The storage type (e.g. @ref Storage::rgb_8_inter).
        */
        template <Storage::type storage_T>
        struct MemLayout {};

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgb_8_inter.
        */
        template <>
        struct MemLayout<Storage::rgb_8_inter> : public GenericInterleavedLayoutRGB, public ChannelOrderRGB
        {
        }; // template struct MemLayout<Storage::rgb_8_inter>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgb_16_inter.
        */
        template <>
        struct MemLayout<Storage::rgb_16_inter> : public GenericInterleavedLayoutRGB, public ChannelOrderRGB
        {
        }; // template struct MemLayout<Storage::rgb_16_inter>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgb_32_inter.
        */
        template <>
        struct MemLayout<Storage::rgb_32_inter> : public GenericInterleavedLayoutRGB, public ChannelOrderRGB
        {
        }; // template struct MemLayout<Storage::rgb_32_inter>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgb_8_planar.
        */
        template <>
        struct MemLayout<Storage::rgb_8_planar> : public GenericPlanarLayoutRGB, public ChannelOrderRGB
        {
        }; // template struct MemLayout<Storage::rgb_8_planar>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgb_16_planar.
        */
        template <>
        struct MemLayout<Storage::rgb_16_planar> : public GenericPlanarLayoutRGB, public ChannelOrderRGB
        {
        }; // template struct MemLayout<Storage::rgb_16_planar>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgb_32_planar.
        */
        template <>
        struct MemLayout<Storage::rgb_32_planar> : public GenericPlanarLayoutRGB, public ChannelOrderRGB
        {
        }; // template struct MemLayout<Storage::rgb_32_planar>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgba_8_inter.
        */
        template <>
        struct MemLayout<Storage::rgba_8_inter> : public GenericInterleavedLayoutRGBA, public ChannelOrderRGBA
        {
        }; // template struct MemLayout<Storage::rgba_8_inter>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgba_16_inter.
        */
        template <>
        struct MemLayout<Storage::rgba_16_inter> : public GenericInterleavedLayoutRGBA, public ChannelOrderRGBA
        {
        }; // template struct MemLayout<Storage::rgba_16_inter>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgba_32_inter.
        */
        template <>
        struct MemLayout<Storage::rgba_32_inter> : public GenericInterleavedLayoutRGBA, public ChannelOrderRGBA
        {
        }; // template struct MemLayout<Storage::rgba_32_inter>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgba_8_planar.
        */
        template <>
        struct MemLayout<Storage::rgba_8_planar> : public GenericPlanarLayoutRGBA, public ChannelOrderRGBA
        {
        }; // template struct MemLayout<Storage::rgba_8_planar>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgba_16_planar.
        */
        template <>
        struct MemLayout<Storage::rgba_16_planar> : public GenericPlanarLayoutRGBA, public ChannelOrderRGBA
        {
        }; // template struct MemLayout<Storage::rgba_16_planar>

        /**
        * @brief Specialisation of @ref MemLayout for @ref Storage::rgba_32_planar.
        */
        template <>
        struct MemLayout<Storage::rgba_32_planar> : public GenericPlanarLayoutRGBA, public ChannelOrderRGBA
        {
        }; // template struct MemLayout<Storage::rgba_32_planar>

    } // namespace phtr::mem

} // namespace phtr

#endif // PHTR_MEM_LAYOUT_H__
