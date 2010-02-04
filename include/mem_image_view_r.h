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

#ifndef __MEM_IMAGE_VIEW_R_H__
#define __MEM_IMAGE_VIEW_R_H__

#include "mem_image_view_base.h"
#include "mem_image_iter_r.h"
#include "channel_type.h"

namespace phtr
{

    /**
    * \brief Class template implementing a (reading) 'image view' of a given
    *  memory position.
    * \details The template uses internal templates to deal efficiently with
    * different storage types.
    * \param T The storage type (e.g. \ref Storage::rgb_8_inter).
    */
    template <Storage::type T>
    class MemImageViewR : public MemImageViewBase<T>
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief The type of the internal storage info object.
            */
            typedef typename MemImageViewBase<T>::storage_info_t storage_info_t;

        public:
            /**
            * \brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename MemImageViewBase<T>::channel_storage_t channel_storage_t;

        public:
            /**
            * \brief The type of the internal iterator.
            */
            typedef typename phtr::MemImageIterR<T> iter_t;

        public:
            /**
            * \brief Constructor.
            * \param base_addr The base address of the image data in memory.
            * \param width The image width.
            * \param height The image height.
            */
            MemImageViewR(const void* base_addr,
                          coord_t width,
                          coord_t height);

        public:
            /**
            * \brief Desctructor.
            */
            ~MemImageViewR();

        public:
            /**
            * \brief Read the 'red' channel value.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            channel_storage_t
            get_px_val_r(coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the 'green' channel value.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            channel_storage_t
            get_px_val_g(coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the 'blue' channel value.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            channel_storage_t
            get_px_val_b(coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the given channel value.
            * \param chan The channel.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            inline channel_storage_t
            get_px_val(Channel::type chan, coord_t x, coord_t y) const;

        public:
            /**
            * \brief Get a pixel iterator.
            * A new iterator is instatiated and a pointer to it is returned
            * (this is necessary since C++ does not support to return polymorphic
            * objects 'by value').
            * \return The iterator.
            */
            iter_t get_iter(coord_t x, coord_t y) const;

    }; // template class MemImageViewR<>

} // namespace phtr

#include "mem_image_view_r.tpl.h"

#endif // __MEM_IMAGE_VIEW_R_H__
