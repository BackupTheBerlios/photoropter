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

#ifndef __PHTR_IMAGE_BUFFER_IMPL_H__
#define __PHTR_IMAGE_BUFFER_IMPL_H__

#include <photoropter/image_buffer.h>
#include <photoropter/types.h>
#include <photoropter/mem/storage_type.h>
#include <photoropter/mem/channel_storage.h>
#include <photoropter/mem/mem_storage_info.h>

namespace phtr
{

    /**
    * @brief Class template for managing an image buffer.
    * @param storage_T The storage type (e.g. @ref mem::Storage::rgb_8_inter).
    */
    template <mem::Storage::type storage_T>
    class ImageBuffer
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief The channel storage type.
            */
            typedef typename mem::ChannelStorage<storage_T>::type channel_storage_t;

        public:
            /**
            * @brief The type of the internal storage info object.
            */
            typedef typename mem::MemStorageInfo<storage_T> storage_info_t;

        public:
            /**
            * @brief Constructor.
            * @param[in] width  Image width.
            * @param[in] height Image height.
            * @param[in] zero   If 'true', the memory will be filled with zeroes.
            */
            ImageBuffer(coord_t width, coord_t height, bool zero = false);

        public:
            /**
            * @brief Destructor.
            */
            ~ImageBuffer();

        public:
            /**
            * @brief Return a pointer to the data the buffer holds.
            * @return Pointer to the data.
            */
            void* data();

        public:
            /**
            * @brief Return the number of pixels the buffer can hold.
            * @return The number of pixels.
            */
            size_t num_pixels();

        public:
            /**
            * @brief Return the number of bytes the buffer holds.
            * @return The number of bytes.
            */
            size_t num_bytes();

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * @brief Copy constructor (disabled).
            */
            ImageBuffer(const ImageBuffer<storage_T>& orig);

        private:
            /**
            * @brief Assignment operator (disabled).
            */
            ImageBuffer<storage_T>& operator=(const ImageBuffer<storage_T>& orig);

        private:
            /**
            * @brief The internal storage info object.
            */
            storage_info_t storage_info_;

        private:
            /**
            * @brief Pointer to the image buffer.
            */
            channel_storage_t* data_;

        private:
            /**
            * @brief The image width.
            */
            coord_t width_;

        private:
            /**
            * @brief The image height.
            */
            coord_t height_;

        private:
            /**
            * @brief The number of channels (e.g., 3).
            */
            size_t num_channels_;

        private:
            /**
            * @brief The number of pixels in the buffer.
            */
            size_t num_pixels_;

        private:
            /**
            * @brief The number of bytes in the buffer.
            */
            size_t num_bytes_;

    };

} // namespace phtr

#include <photoropter/image_buffer.tpl.h>

#endif // __PHTR_IMAGE_BUFFER_IMPL_H__
