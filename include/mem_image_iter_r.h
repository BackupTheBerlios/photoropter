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

#ifndef __MEM_IMAGE_ITER_R_H__
#define __MEM_IMAGE_ITER_R_H__

#include "mem_image_iter_base.h"
#include "channel_type.h"

namespace phtr
{

    /**
    * \brief Iterator class for read access to an image in memory.
    * \details Instances of this class are usually created by \ref MemImageViewR.
    * \param T The storage type (e.g. \ref Storage::rgb_8_inter).
    */
    template <Storage::type T>
    class MemImageIterR : public MemImageIterBase<T>
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief Struct describing the memory layout.
            */
            typedef typename MemImageIterBase<T>::mem_layout_t mem_layout_t;

        public:
            /**
            * \brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename MemImageIterBase<T>::channel_storage_t channel_storage_t;

        public:
            /**
            * \brief Constructor.
            * \param[in] base_addr The base address (i.e., top left corner).
            * \param[in] px_offs   The current pixel offset.
            * \param[in] step      The pixel step.
            * \param[in] line_step The line step.
            * \param[in] r_offs    The 'red' channel offset.
            * \param[in] g_offs    The 'green' channel offset.
            * \param[in] b_offs    The 'blue' channel offset.
            */
            MemImageIterR(channel_storage_t* base_addr, size_t px_offs,
                          size_t step, size_t line_step,
                          size_t r_offs, size_t g_offs, size_t b_offs);

        public:
            /**
            * \brief Read the 'red' channel value.
            * \return The value.
            */
            channel_storage_t get_px_val_r();

        public:
            /**
            * \brief Read the 'green' channel value.
            * \return The value.
            */
            channel_storage_t get_px_val_g();

        public:
            /**
            * \brief Read the 'blue' channel value.
            * \return The value.
            */
            channel_storage_t get_px_val_b();

        public:
            /**
            * \brief Read the value for the given channel.
            * \param channel The channel.
            * \return The value.
            */
            inline channel_storage_t get_px_val(Channel::type channel);

    }; // template class MemImageIterR<>

} // namespace phtr

#include "mem_image_iter_r.tpl.h"

#endif // __MEM_IMAGE_ITER_R_H__
