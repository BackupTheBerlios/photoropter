#ifndef __MEM_IMAGE_VIEW_ITER_W_H__
#define __MEM_IMAGE_VIEW_ITER_W_H__

#include "image_view.h"
#include "storage_type.h"
#include "mem_layout.h"

namespace phtr
{

    template <Storage::type T>
    class MemImageViewIterW : public IImageViewIterW
    {

        public:
            typedef typename phtr::MemLayout<T> mem_layout_t;

        public:
            /**
            * \brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename ChannelStorage<T>::type channel_storage_t;

        public:
            MemImageViewIterW(coord_t width, coord_t height, channel_storage_t* addr);

        public:
            virtual ~MemImageViewIterW();

        public:
            /**
            * \brief Write the 'red' channel value to the current pixel.
            * \param val  The value.
            */
            virtual void write_px_val_r(channel_t val);

        public:
            /**
            * \brief Write the 'green' channel value to the current pixel.
            * \param val  The value.
            */
            virtual void write_px_val_g(channel_t val);

        public:
            /**
            * \brief Write the 'blue' channel value to the current pixel.
            * \param val  The value.
            */
            virtual void write_px_val_b(channel_t val);

        public:
            /**
            * \brief Increment the current position.
            * \attention Boundary checks are not guaranteed.
            */
            virtual void inc_pos();

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
            const size_t step_;

        private:
            const size_t r_offs_;

        private:
            const size_t g_offs_;

        private:
            const size_t b_offs_;

    }; // class MemImageViewIterW

} // namespace phtr

#include "mem_image_view_iter_w.tpl.h"

#endif // __MEM_IMAGE_VIEW_ITER_W_H__
