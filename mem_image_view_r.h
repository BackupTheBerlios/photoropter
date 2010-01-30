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
#include "image_view.h"

namespace phtr
{

    /**
    * \brief Class template implementing a (reading) 'image view' of a given
    *  memory position.
    * \details The template uses internal templates to deal efficiently with
    * different storage types.
    */
    template <Storage::type T>
    class MemImageViewR : public IImageViewR, public MemImageViewBase<T>
    {

            /* ****************************************
             * public interface
             * **************************************** */

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
            virtual ~MemImageViewR();

        public:
            /**
            * \brief Read the 'red' channel value.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_r(coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the 'green' channel value.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_g(coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the 'blue' channel value.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_b(coord_t x, coord_t y) const;

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief Scale a pixel value to the [0:1] interval.
            * \param raw_val The raw (i.e., stored) value.
            */
            channel_t scale_px(typename MemImageViewBase<T>::channel_storage_t raw_val) const;

    }; // template class MemImageViewR

} // namespace phtr

#include "mem_image_view_r.tpl.h"

#endif // __MEM_IMAGE_VIEW_R_H__
