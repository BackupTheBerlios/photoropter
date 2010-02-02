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

#ifndef __MEM_IMAGE_VIEW_ITER_W_H__
#define __MEM_IMAGE_VIEW_ITER_W_H__

#include "storage_type.h"
#include "channel_range.h"
#include "mem_layout.h"

namespace phtr
{

    /**
    * \brief Iterator class for write access to an image in memory.
    * \details Instances of this class are usually created by \ref MemImageViewW.
    */
    template <Storage::type T>
    class MemImageViewIterW
    {

            /* ****************************************
             * public interface
             * **************************************** */
        public:
            /**
            * \brief Struct describing the memory layout.
            */
            typedef typename phtr::MemLayout<T> mem_layout_t;

        public:
            /**
            * \brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename ChannelStorage<T>::type channel_storage_t;

        public:
            /**
            * \brief Constructor.
            */
            MemImageViewIterW(coord_t width, coord_t height, channel_storage_t* addr);

        public:
            /**
            * \brief Destructor.
            */
            ~MemImageViewIterW();

        public:
            /**
            * \brief Write the 'red' channel value to the current pixel.
            * \param val  The value.
            */
            void write_px_val_r(channel_storage_t val);

        public:
            /**
            * \brief Write the 'green' channel value to the current pixel.
            * \param val  The value.
            */
            void write_px_val_g(channel_storage_t val);

        public:
            /**
            * \brief Write the 'blue' channel value to the current pixel.
            * \param val  The value.
            */
            void write_px_val_b(channel_storage_t val);

        public:
            /**
            * \brief Increment the current position (horizontally).
            * \attention Boundary checks are currently not implemented.
            */
            void inc_x();

        public:
            /**
            * \brief Decrement the current position (horizontally).
            * \attention Boundary checks are currently not implemented.
            */
            void dec_x();

        public:
            /**
            * \brief Increment the current position (vertically).
            * \attention Boundary checks are currently not implemented.
            */
            void inc_y();

        public:
            /**
            * \brief Decrement the current position (vertically).
            * \attention Boundary checks are currently not implemented.
            */
            void dec_y();

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief The current address.
            */
            channel_storage_t* addr_;

        private:
            /**
            * \brief The storage type.
            */
            const Storage::type storage_type_;

        private:
            /**
            * \brief The step between adjacent pixels.
            */
            const size_t step_;

        private:
            /**
            * \brief The step between lines.
            */
            const size_t line_step_;

        private:
            /**
            * \brief The offset of the 'red' channel.
            */
            const size_t r_offs_;

        private:
            /**
            * \brief The offset of the 'green' channel.
            */
            const size_t g_offs_;

        private:
            /**
            * \brief The offset of the 'blue' channel.
            */
            const size_t b_offs_;

        protected:
            /**
            * \brief The minimal value a channel can hold.
            */
            const channel_storage_t min_chan_val_;

        protected:
            /**
            * \brief The maximal value a channel can hold.
            */
            const channel_storage_t max_chan_val_;


    }; // class MemImageViewIterW

} // namespace phtr

#include "mem_image_view_iter_w.tpl.h"

#endif // __MEM_IMAGE_VIEW_ITER_W_H__
