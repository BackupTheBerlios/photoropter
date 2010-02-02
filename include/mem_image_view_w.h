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

#ifndef __MEM_IMAGE_VIEW_W_H__
#define __MEM_IMAGE_VIEW_W_H__

#include "storage_type.h"
#include "mem_storage_info.h"
#include "mem_image_view_iter_w.h"

namespace phtr
{

    /**
    * \brief Class template implementing a (writing) 'image view' of a given
    *  memory position.
    * \details The template uses internal templates to deal efficiently with
    * different storage types.
    */
    template <Storage::type T>
    class MemImageViewW : public MemImageViewBase<T>
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
            typedef typename phtr::MemImageViewIterW<T> iter_t;

        public:
            /**
            * \brief Constructor.
            * \param base_addr The base address of the image data in memory.
            * \param width The image width.
            * \param height The image height.
            */
            MemImageViewW(void* base_addr,
                          coord_t width,
                          coord_t height);

        public:
            /**
            * \brief Desctructor.
            */
            ~MemImageViewW();

        public:
            /**
            * \brief Write the 'red' channel value.
            * \param x   The x coordinate.
            * \param y   The y coordinate.
            * \param val The channel value.
            */
            void write_px_val_r(coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * \brief Write the 'green' channel value.
            * \param x   The x coordinate.
            * \param y   The y coordinate.
            * \param val The channel value.
            */
            void write_px_val_g(coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * \brief Write the 'blue' channel value.
            * \param x   The x coordinate.
            * \param y   The y coordinate.
            * \param val The channel value.
            */
            void write_px_val_b(coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * \brief Get a pixel iterator.
            * A new iterator is instatiated and a pointer to it is returned
            * (this is necessary since C++ does not support to return polymorphic
            * objects 'by value').
            * \return The iterator.
            */
            iter_t* get_iter(coord_t x, coord_t y);

        public:
            /**
            * \brief Set the region of interest.
            * \param x_min The minimal x coordinate.
            * \param y_min The minimal y coordinate.
            * \param x_max The maximal x coordinate.
            * \param y_max The maximal y coordinate.
            */
            void set_roi(coord_t x_min, coord_t y_min, coord_t x_max, coord_t y_max);

        public:
            /**
            * \brief Get the current region of interest.
            * \param x_min The minimal x coordinate.
            * \param y_min The minimal y coordinate.
            * \param x_max The maximal x coordinate.
            * \param y_max The maximal y coordinate.
            */
            void get_roi(coord_t& x_min, coord_t& y_min, coord_t& x_max, coord_t& y_max);

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief The position of the left edge of the region of interest.
            */
            coord_t roi_x_min_;

        private:
            /**
            * \brief The position of the right edge of the region of interest.
            */
            coord_t roi_x_max_;

        private:
            /**
            * \brief The position of the lower edge of the region of interest.
            */
            coord_t roi_y_min_;

        private:
            /**
            * \brief The position of the top edge of the region of interest.
            */
            coord_t roi_y_max_;


    }; // template class MemImageViewW

} // namespace phtr

#include "mem_image_view_w.tpl.h"

#endif // __MEM_IMAGE_VIEW_W_H__
