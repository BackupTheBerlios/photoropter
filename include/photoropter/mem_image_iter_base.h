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

#ifndef __PHTR_MEM_IMAGE_ITER_BASE_H__
#define __PHTR_MEM_IMAGE_ITER_BASE_H__

#include <photoropter/storage_type.h>
#include <photoropter/channel_range.h>
#include <photoropter/mem_layout.h>

namespace phtr
{

    /**
    * @brief Base class template for iterator classes. Not supposed to be used directly.
    * See @ref MemImageIterR and @ref MemImageIterW for details.
    * @param T The storage type (e.g. @ref mem::Storage::rgb_8_inter).
    */
    template <mem::Storage::type T>
    class MemImageIterBase
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief Struct describing the memory layout.
            */
            typedef typename mem::MemLayout<T> mem_layout_t;

        public:
            /**
            * @brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename mem::ChannelStorage<T>::type channel_storage_t;

        public:
            /**
            * @brief Increment the current position (horizontally).
            * @attention Boundary checks are currently not implemented.
            */
            void inc_x();

        public:
            /**
            * @brief Decrement the current position (horizontally).
            * @attention Boundary checks are currently not implemented.
            */
            void dec_x();

        public:
            /**
            * @brief Increment the current position (vertically).
            * @attention Boundary checks are currently not implemented.
            */
            void inc_y();

        public:
            /**
            * @brief Decrement the current position (vertically).
            * @attention Boundary checks are currently not implemented.
            */
            void dec_y();

        public:
            /**
            * @brief Set the pixel offset.
            * @param[in] px_offs The new pixel offset.
            */
            void set_px_offs(size_t px_offs);

            /* ****************************************
             * internals
             * **************************************** */

        protected:
            /**
            * @brief Constructor.
            * @param[in] base_addr The base address (i.e., top left corner).
            * @param[in] px_offs   The current pixel offset.
            * @param[in] step      The pixel step.
            * @param[in] line_step The line step.
            * @param[in] r_offs    The 'red' channel offset.
            * @param[in] g_offs    The 'green' channel offset.
            * @param[in] b_offs    The 'blue' channel offset.
            */
            MemImageIterBase(channel_storage_t* base_addr, size_t px_offs,
                             size_t step, size_t line_step,
                             size_t r_offs, size_t g_offs, size_t b_offs);

        protected:
            /**
            * @brief The current address.
            */
            channel_storage_t* base_addr_;

        protected:
            /**
            * @brief The current pixel offset.
            */
            size_t px_offs_;

        protected:
            /**
            * @brief The storage type.
            */
            const mem::Storage::type storage_type_;

        protected:
            /**
            * @brief The step between adjacent pixels.
            */
            const size_t step_;

        protected:
            /**
            * @brief The step between lines.
            */
            const size_t line_step_;

        protected:
            /**
            * @brief The offset of the 'red' channel.
            */
            const size_t r_offs_;

        protected:
            /**
            * @brief The offset of the 'green' channel.
            */
            const size_t g_offs_;

        protected:
            /**
            * @brief The offset of the 'blue' channel.
            */
            const size_t b_offs_;

    }; // template class MemImageIterBase<>

} // namespace phtr

#include <photoropter/mem_image_iter_base.tpl.h>

#endif // __PHTR_MEM_IMAGE_ITER_BASE_H__
