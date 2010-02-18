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

#ifndef __PHTR_MEM_IMAGE_VIEW_R_H__
#define __PHTR_MEM_IMAGE_VIEW_R_H__

#include <photoropter/mem_image_view_base.h>
#include <photoropter/mem_image_iter_r.h>
#include <photoropter/channel_type.h>

namespace phtr
{

    /**
    * @brief Class template implementing a (reading) 'image view' of a given
    *  memory position.
    * @details The template uses internal templates to deal efficiently with
    * different storage types.
    * @param T The storage type (e.g. @ref mem::Storage::rgb_8_inter).
    */
    template <mem::Storage::type T>
    class MemImageViewR : public MemImageViewBase<T>
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief The type of the internal storage info object.
            */
            typedef typename MemImageViewBase<T>::storage_info_t storage_info_t;

        public:
            /**
            * @brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename MemImageViewBase<T>::channel_storage_t channel_storage_t;

        public:
            /**
            * @brief The type of the internal iterator.
            */
            typedef typename phtr::MemImageIterR<T> iter_t;

        public:
            /**
            * @brief Constructor.
            * @param[in] base_addr The base address of the image data in memory.
            * @param[in] width The image width.
            * @param[in] height The image height.
            */
            MemImageViewR(const void* base_addr,
                          coord_t width,
                          coord_t height);

        public:
            /**
            * @brief Read the given channel value.
            * @param[in] chan The channel.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The channel value.
            */
            inline channel_storage_t
            get_px_val(Channel::type chan, coord_t x, coord_t y) const;

        public:
            /**
            * @brief Get a pixel iterator.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The iterator.
            */
            iter_t get_iter(coord_t x, coord_t y) const;

        public:
            /**
            * @brief Set the aspect ratio of the image.
            * @param aspect_ratio The new aspect ratio.
            */
            void set_aspect_ratio(interp_coord_t aspect_ratio);

        public:
            /**
            * @brief Get the aspect ratio of the image.
            * @note The ratio is automatically calculated when the image is created,
            * but can be overridden using @ref set_aspect_ratio().
            * @return The aspect ratio.
            */
            interp_coord_t aspect_ratio() const;

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * @brief The image's aspect ratio.
            */
            interp_coord_t aspect_ratio_;

    }; // template class MemImageViewR<>

} // namespace phtr

#include <photoropter/mem_image_view_r.tpl.h>

#endif // __PHTR_MEM_IMAGE_VIEW_R_H__
