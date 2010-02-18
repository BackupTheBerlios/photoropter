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

#ifndef __PHTR_MEM_IMAGE_VIEW_BASE_H__
#define __PHTR_MEM_IMAGE_VIEW_BASE_H__

#include <photoropter/storage_type.h>
#include <photoropter/mem_storage_info.h>

/**
* @brief Main namespace of the Photoropter library.
*/
namespace phtr
{

    /**
    * @brief Base class template for image views. See @ref MemImageViewR and
    * @ref MemImageViewW for details.
    * @param T The storage type (e.g. @ref mem::Storage::rgb_8_inter).
    */
    template <mem::Storage::type T>
    class MemImageViewBase
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief The type of the internal storage info object.
            */
            typedef typename mem::MemStorageInfo<T> storage_info_t;

        public:
            /**
            * @brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename storage_info_t::channel_storage_t channel_storage_t;

        public:
            /**
            * @brief Get the image width.
            * @return The width.
            */
            coord_t width() const;

        public:
            /**
            * @brief Get the image height.
            * @return The height.
            */
            coord_t height() const;

        public:
            /**
            * @brief Determine the 'pixel offset' to a given set of coordinates.
            * @param[in] x The x coordinate.
            * @param[in] y The y coordinate.
            * @return The offset
            */
            size_t get_px_offs(coord_t x, coord_t y) const;

            /* ****************************************
             * internals
             * **************************************** */

            ///@cond PROTECTED
        protected:
            /**
            * @brief Constructor.
            * @param[in] base_addr The base address of the image data in memory.
            * @param[in] width The image width.
            * @param[in] height The image height.
            */
            MemImageViewBase(void* base_addr,
                             coord_t width,
                             coord_t height);

        protected:
            /**
            * @brief The storage type of the image.
            */
            const mem::Storage::type storage_type_;

        protected:
            /**
            * @brief Internal storage info object, used to calculate the memory
            * layout parameters.
            */
            const storage_info_t storage_info_;

        protected:
            /**
            * @brief The base address of the image.
            */
            channel_storage_t* base_addr_;

        protected:
            /**
            * @brief The image width.
            */
            const coord_t width_;

        protected:
            /**
            * @brief The image height.
            */
            const coord_t height_;

        protected:
            /**
            * @brief The minimal value a channel can hold.
            */
            const channel_storage_t min_chan_val_;

        protected:
            /**
            * @brief The maximal value a channel can hold.
            */
            const channel_storage_t max_chan_val_;

        protected:
            /**
            * @brief The distance between two adjacent pixels, in multiples
            * of the channel storage unit.
            */
            const size_t step_;

        protected:
            /**
            * @brief The distance between two adjacent lines, in multiples
            * of the channel storage unit.
            */
            const size_t line_step_;

        protected:
            /**
            * @brief The offset of the red channel to the current memory position.
            */
            const size_t r_offs_;

        protected:
            /**
            * @brief The offset of the green channel to the current memory position.
            */
            const size_t g_offs_;

        protected:
            /**
            * @brief The offset of the blue channel to the current memory position.
            */
            const size_t b_offs_;
            ///@endcond

    }; // template class MemImageViewBase<>

} // namespace phtr

#include <photoropter/mem_image_view_base.tpl.h>

#endif // __PHTR_MEM_IMAGE_VIEW_BASE_H__
