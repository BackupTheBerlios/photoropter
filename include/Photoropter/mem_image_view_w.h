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

#include "Photoropter/mem_image_view_base.h"
#include "Photoropter/mem_image_iter_w.h"
#include "Photoropter/channel_type.h"

namespace phtr
{

    /**
    * \brief Class template implementing a (writing) 'image view' of a given
    *  memory position.
    * \details The template uses internal templates to deal efficiently with
    * different storage types.
    * \param T The storage type (e.g. \ref Storage::rgb_8_inter).
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
            typedef typename phtr::MemImageIterW<T> iter_t;

        public:
            /**
            * \brief Constructor.
            * \param[in] base_addr The base address of the image data in memory.
            * \param[in] width The image width.
            * \param[in] height The image height.
            */
            MemImageViewW(void* base_addr,
                          coord_t width,
                          coord_t height);

        public:
            /**
            * \brief Write the 'red' channel value.
            * \param[in] x   The x coordinate.
            * \param[in] y   The y coordinate.
            * \param[in] val The channel value.
            */
            void write_px_val_r(coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * \brief Write the 'green' channel value.
            * \param[in] x   The x coordinate.
            * \param[in] y   The y coordinate.
            * \param[in] val The channel value.
            */
            void write_px_val_g(coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * \brief Write the 'blue' channel value.
            * \param[in] x   The x coordinate.
            * \param[in] y   The y coordinate.
            * \param[in] val The channel value.
            */
            void write_px_val_b(coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * \brief Write the given channel value.
            * \param[in] chan The channel.
            * \param[in] x    The x coordinate.
            * \param[in] y    The y coordinate.
            * \param[in] val  The channel value.
            */
            inline void write_px_val(Channel::type chan, coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * \brief Get a pixel iterator.
            * \param[in] x    The x coordinate.
            * \param[in] y    The y coordinate.
            * \return The iterator.
            */
            iter_t get_iter(coord_t x, coord_t y);

        public:
            /**
            * \brief Set the region of interest.
            * \details A ROI of (0, 0, width, height) corresponds to the entire image.
            * \param[in] x_min The minimal x coordinate.
            * \param[in] y_min The minimal y coordinate.
            * \param[in] x_limit The x coordinate limit (maximal value + 1).
            * \param[in] y_limit The y coordinate limit (maximal value + 1).
            */
            void set_roi(coord_t x_min, coord_t y_min, coord_t x_limit, coord_t y_limit);

        public:
            /**
            * \brief Get the current region of interest.
            * \details A ROI of (0, 0, width, height) corresponds to the entire image.
            * \param[out] x_min The minimal x coordinate.
            * \param[out] y_min The minimal y coordinate.
            * \param[out] x_limit The x coordinate limit (maximal value + 1).
            * \param[out] y_limit The y coordinate limit (maximal value + 1).
            */
            void get_roi(coord_t& x_min, coord_t& y_min, coord_t& x_limit, coord_t& y_limit);

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
            coord_t roi_x_limit_;

        private:
            /**
            * \brief The position of the lower edge of the region of interest.
            */
            coord_t roi_y_min_;

        private:
            /**
            * \brief The position of the top edge of the region of interest.
            */
            coord_t roi_y_limit_;


    }; // template class MemImageViewW<>

} // namespace phtr

#include "Photoropter/mem_image_view_w.tpl.h"

#endif // __MEM_IMAGE_VIEW_W_H__
