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

#ifndef __IMAGE_BUFFER_H__
#define __IMAGE_BUFFER_H__

#include "types.h"
#include "storage_type.h"

namespace phtr
{
    /**
    * \brief Interface class representing a buffer for an image.
    */
    class IImageBuffer
    {

        public:
            /**
            * \brief Return a pointer to the data the buffer holds.
            * \return Pointer to the data.
            */
            virtual void* data() = 0;

        public:
            /**
            * \brief Return the number of pixels the buffer can hold.
            * \return The number of pixels.
            */
            virtual size_t num_pixels() = 0;

        public:
            /**
            * \brief Return the number of bytes the buffer holds.
            * \return The number of bytes.
            */
            virtual size_t num_bytes() = 0;

        public:
            /**
            * \brief Get an image buffer instance.
            * \param storage_type The storage type (e.g., \ref Storage::rgb_8_inter).
            * \param width The image width.
            * \param height The image height.
            * \return Pointer to the buffer object.
            */
            static IImageBuffer* get_image_buffer(phtr::Storage::type storage_type,
                                                  coord_t width,
                                                  coord_t height);

        public:
            /**
            * \brief Destructor.
            * \note Declared 'virtual' for proper polymorphic behaviour.
            */
            virtual ~IImageBuffer()
            {
                //NIL
            }

        protected:
            /**
            * \brief Constructor.
            */
            IImageBuffer()
            {
                //NIL
            }

    }; // class IImageBuffer

} // namespace phtr

#endif // __IMAGE_BUFFER_H__
