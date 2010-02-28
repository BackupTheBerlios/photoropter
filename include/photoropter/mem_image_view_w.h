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

#ifndef PHTR_MEM_IMAGE_VIEW_W_H__
#define PHTR_MEM_IMAGE_VIEW_W_H__

#include <photoropter/mem/coord_tuple.h>
#include <photoropter/mem/colour_tuple.h>
#include <photoropter/mem/channel_type.h>
#include <photoropter/mem_image_view_base.h>
#include <photoropter/mem_image_iter_w.h>

namespace phtr
{

    /**
    * @brief Class template implementing a (writing) 'image view' of a given
    *  memory position.
    * @details The template uses internal templates to deal efficiently with
    * different storage types. Both a region of interest (ROI) and a 'parent window'
    * size/offset can be specified to deal with different cases of sub-picture rendering.
    * @param storage_T The storage type (e.g. @ref mem::Storage::rgb_8_inter).
    */
    template <mem::Storage::type storage_T>
    class MemImageViewW : public MemImageViewBase<storage_T>
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief The type of the internal storage info object.
            */
            typedef typename MemImageViewBase<storage_T>::storage_info_t storage_info_t;

        public:
            /**
            * @brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename MemImageViewBase<storage_T>::channel_storage_t channel_storage_t;

        public:
            /**
            * @brief The type of the internal iterator.
            */
            typedef typename phtr::MemImageIterW<storage_T> iter_t;

        public:
            /**
            * @brief Constructor.
            * @param[in] base_addr The base address of the image data in memory.
            * @param[in] width The image width.
            * @param[in] height The image height.
            */
            MemImageViewW(void* base_addr,
                          coord_t width,
                          coord_t height);

        public:
            /**
            * @brief Write the given channel value.
            * @param[in] chan The channel.
            * @param[in] x    The x coordinate.
            * @param[in] y    The y coordinate.
            * @param[in] val  The channel value.
            */
            inline void write_px_val(Channel::type chan, coord_t x, coord_t y, channel_storage_t val);

        public:
            /**
            * @brief Write RGB channel values to a pixel.
            * @param[in] coords The coordinates.
            * @param[in] values The channel values.
            */
            template <typename coord_tuple_T>
            inline void write_px_vals(const coord_tuple_T& coords,
                                      const typename coord_tuple_T::channel_order_t::colour_tuple_t& values);

        public:
            /**
            * @brief Get a pixel iterator.
            * @param[in] x    The x coordinate.
            * @param[in] y    The y coordinate.
            * @return The iterator.
            */
            iter_t get_iter(coord_t x, coord_t y);

        public:
            /**
            * @brief Set the region of interest.
            * @details The region of interest describes a rectangle to which all image operations
            * should be limited. This is mainly a performance help. A ROI of (0, 0, width, height)
            * corresponds to the entire image.
            * @param[in] x_min The minimal x coordinate.
            * @param[in] y_min The minimal y coordinate.
            * @param[in] x_limit The x coordinate limit (maximal value + 1).
            * @param[in] y_limit The y coordinate limit (maximal value + 1).
            */
            void set_roi(coord_t x_min, coord_t y_min, coord_t x_limit, coord_t y_limit);

        public:
            /**
            * @brief Get the current region of interest.
            * @details The region of interest describes a rectangle to which all image operations
            * should be limited. This is mainly a performance help. A ROI of (0, 0, width, height)
            * corresponds to the entire image.
            * @param[out] x_min The minimal x coordinate.
            * @param[out] y_min The minimal y coordinate.
            * @param[out] x_limit The x coordinate limit (maximal value + 1).
            * @param[out] y_limit The y coordinate limit (maximal value + 1).
            */
            void get_roi(coord_t& x_min, coord_t& y_min, coord_t& x_limit, coord_t& y_limit);

        public:
            /**
            * @brief Set the parent window position.
            * @details Set the offset and size of this view's "parent" window. The view is interpreted
            * as a part of a larger, "virtual" frame. Its offset is given relative to the parent's upper
            * left edge, as well as the parent window size. By using this mechanism, the current
            * view sort itself is interpreted like a region of interest: the complete image can be
            * rendered by processing multiple smaller sub-buffers. By default, the offset is set to
            * (0,0) and the parent window size is set to the current view size.
            * @param[in] offs_x The horizontal offset relative to the parent's upper left edge.
            * @param[in] offs_y The vertical offset relative to the parent's upper left edge.
            * @param[in] width The parent window's width.
            * @param[in] height The parent window's height.
            */
            void set_parent_window(coord_t offs_x, coord_t offs_y,
                                   coord_t width, coord_t height);

        public:
            /**
            * @brief Set the parent window position.
            * @details Set the offset and size of this view's "parent" window. The view is interpreted
            * as a part of a larger, "virtual" frame. Its offset is given relative to the parent's upper
            * left edge, as well as the parent window size. By using this mechanism, the current
            * view sort itself is interpreted like a region of interest: the complete image can be
            * rendered by processing multiple smaller sub-buffers. By default, the offset is set to
            * (0,0) and the parent window size is set to the current view size.
            * @param[out] offs_x The horizontal offset relative to the parent's upper left edge.
            * @param[out] offs_y The vertical offset relative to the parent's upper left edge.
            * @param[out] width The parent window's width.
            * @param[out] height The parent window's height.
            */
            void get_parent_window(coord_t& offs_x, coord_t& offs_y,
                                   coord_t& width, coord_t& height);

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * @brief The position of the left edge of the region of interest.
            */
            coord_t roi_x_min_;

        private:
            /**
            * @brief The position of the right edge of the region of interest.
            */
            coord_t roi_x_limit_;

        private:
            /**
            * @brief The position of the lower edge of the region of interest.
            */
            coord_t roi_y_min_;

        private:
            /**
            * @brief The position of the top edge of the region of interest.
            */
            coord_t roi_y_limit_;

        private:
            /**
            * @brief The horizontal offset relative to the parent's upper left edge.
            */
            coord_t parent_offs_x_;

        private:
            /**
            * @brief The vertical offset relative to the parent's upper left edge.
            */
            coord_t parent_offs_y_;

        private:
            /**
            * @brief The parent window's width.
            */
            coord_t parent_width_;

        private:
            /**
            * @brief The parent window's height.
            */
            coord_t parent_height_;


    }; // template class MemImageViewW<>

} // namespace phtr

#include <photoropter/mem_image_view_w.tpl.h>

#endif // PHTR_MEM_IMAGE_VIEW_W_H__
