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

#ifndef __PHTR_MEM_STORAGE_INFO_H__
#define __PHTR_MEM_STORAGE_INFO_H__

#include <limits>

#include <photoropter/storage_type.h>
#include <photoropter/channel_range.h>
#include <photoropter/channel_storage.h>
#include <photoropter/mem_layout.h>

namespace phtr
{

    namespace mem
    {

        /**
        * @brief Template providing details on the memory storage of a given
        * image type.
        * @param T The storage type (e.g. @ref Storage::rgb_8_inter).
        */
        template <Storage::type T>
        struct MemStorageInfo
        {
            /**
            * @brief The channel storage type (e.g., uint8_t).
            */
            typedef typename ChannelStorage<T>::type channel_storage_t;

            /**
            * @brief The memory layout.
            */
            typedef mem::MemLayout<T> mem_layout_t;

            /**
            * @brief Constructor.
            * @param[in] width  The image width.
            * @param[in] height The image height.
            */
            MemStorageInfo(coord_t width, coord_t height)
                    : width(width),
                    height(height),
                    min_val(ChannelRange<T>::min()),
                    max_val(ChannelRange<T>::max()),
                    step(mem_layout_t::step(width, height)),
                    line_step(mem_layout_t::line_step(width, height)),
                    num_channels(mem_layout_t::num_channels()),
                    r_offs(mem_layout_t::r_offs(width, height)),
                    g_offs(mem_layout_t::g_offs(width, height)),
                    b_offs(mem_layout_t::b_offs(width, height))
            {
            }

            /**
            * @brief The image width.
            */
            const coord_t width;

            /**
            * @brief The image height.
            */
            const coord_t height;

            /**
            * @brief The minimal value a channel can store (e.g. 0 for unsigned types).
            */
            const channel_storage_t min_val;

            /**
            * @brief The maximal value a channel can store (e.g. 255 for uint8_t).
            */
            const channel_storage_t max_val;

            /**
            * @brief The step between pixels, in multiples of the channel
            * storage unit (e.g., 1 for planar images, 3 for interleaved).
            */
            const size_t step;

            /**
            * @brief The step between lines, in multiples of the channel
            * storage unit (e.g., width for planar images, 3*width for interleaved).
            */
            const size_t line_step;

            /**
            * @brief The number of channels (e.g., 3).
            */
            const size_t num_channels;

            /**
            * @brief The offset of the red channel to the current memory position
            (e.g. 0 for RGB).
            */
            const size_t r_offs;

            /**
            * @brief The offset of the blue channel to the current memory
            position (e.g. 1 for RGB interleave, width*height for RGB planar).
            */
            const size_t g_offs;

            /**
            * @brief The offset of the green channel to the current memory
            position (e.g. 2 for RGB interleave, 2*width*height for RGB planar).
            */
            const size_t b_offs;
        }; // template struct MemStorageInfo

    } // namespace phtr::mem

} // namespace phtr

#endif // __PHTR_MEM_STORAGE_INFO_H__
