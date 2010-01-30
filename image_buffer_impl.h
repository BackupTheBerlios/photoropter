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

#ifndef __IMAGE_BUFFER_IMPL_H__
#define __IMAGE_BUFFER_IMPL_H__

#include "image_buffer.h"
#include "types.h"
#include "storage_type.h"
#include "channel_storage.h"
#include "mem_storage_info.h"

namespace phtr
{

    /**
    * \brief Class template implementing the \ref IImageBuffer interface.
    */
    template <phtr::Storage::type T>
    class ImageBufferImpl : public IImageBuffer
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief The channel storage type.
            */
            typedef typename phtr::ChannelStorage<T>::type channel_storage_t;

        public:
            /**
            * \brief The type of the internal storage info object.
            */
            typedef typename phtr::MemStorageInfo<T> storage_info_t;

        public:
            /**
            * \brief Constructor.
            * \param width Image width.
            * \param height Image height.
            */
            ImageBufferImpl(coord_t width, coord_t height);

        public:
            /**
            * \brief Destructor.
            */
            ~ImageBufferImpl();

        public:
            /**
            * \brief Return a pointer to the data the buffer holds.
            * \return Pointer to the data.
            */
            void* data();

        public:
            /**
            * \brief Return the number of pixels the buffer can hold.
            * \return The number of pixels.
            */
            size_t num_pixels();

        public:
            /**
            * \brief Return the number of bytes the buffer holds.
            * \return The number of bytes.
            */
            size_t num_bytes();

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief The internal storage info object.
            */
            storage_info_t storage_info_;

        private:
            /**
            * \brief Pointer to the image buffer.
            */
            channel_storage_t* data_;

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
            * \brief The number of channels (e.g., 3).
            */
            size_t num_channels_;

        private:
            /**
            * \brief The number of pixels in the buffer.
            */
            size_t num_pixels_;

        private:
            /**
            * \brief The number of bytes in the buffer.
            */
            size_t num_bytes_;

    };

} // namespace phtr

#include "image_buffer_impl.tpl.h"

#endif // __IMAGE_BUFFER_IMPL_H__
