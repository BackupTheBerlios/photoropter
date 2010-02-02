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

namespace phtr
{

    /**
    * \brief Iterator class for read access to an image in memory.
    * \details Instances of this class are usually created by \ref MemImageViewR.
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
            */
            MemImageIterR(coord_t width, coord_t height, const channel_storage_t* addr);

        public:
            /**
            * \brief Read the 'red' channel value.
            * \param val  The value.
            */
            channel_storage_t read_px_val_r();

        public:
            /**
            * \brief Read the 'green' channel value.
            * \param val  The value.
            */
            channel_storage_t read_px_val_g();

        public:
            /**
            * \brief Read the 'blue' channel value.
            * \param val  The value.
            */
            channel_storage_t read_px_val_b();

    }; // template class MemImageIterR<>

} // namespace phtr

#include "mem_image_iter_r.tpl.h"

#endif // __MEM_IMAGE_ITER_R_H__
