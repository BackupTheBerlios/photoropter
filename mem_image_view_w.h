#ifndef __MEM_IMAGE_VIEW_W_H__
#define __MEM_IMAGE_VIEW_W_H__

#include "storage_type.h"
#include "image_view.h"
#include "mem_storage_info.h"

namespace phtr
{

    /**
    * \brief Class template implementing a (writing) 'image view' of a given
    *  memory position.
    * \details The template uses internal templates to deal efficiently with
    * different storage types.
    */
    template <Storage::type T>
    class MemImageViewW : public IImageViewW, public MemImageViewBase<T>
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
            MemImageViewW(void* base_addr,
                          coord_t width,
                          coord_t height);

        public:
            /**
            * \brief Desctructor.
            */
            virtual ~MemImageViewW();

        public:
            /**
            * \brief Write the 'red' channel value.
            * \param x   The x coordinate.
            * \param y   The y coordinate.
            * \param val The channel value.
            */
            virtual void write_px_val_r(coord_t x, coord_t y, channel_t val);

        public:
            /**
            * \brief Write the 'green' channel value.
            * \param x   The x coordinate.
            * \param y   The y coordinate.
            * \param val The channel value.
            */
            virtual void write_px_val_g(coord_t x, coord_t y, channel_t val);

        public:
            /**
            * \brief Write the 'blue' channel value.
            * \param x   The x coordinate.
            * \param y   The y coordinate.
            * \param val The channel value.
            */
            virtual void write_px_val_b(coord_t x, coord_t y, channel_t val);

        public:
            /**
            * \brief Get a pixel iterator.
            * A new iterator is instatiated and a pointer to it is returned
            * (this is necessary since C++ does not support to return polymorphic
            * objects 'by value').
            * \return The iterator.
            */
            IImageViewIterW* get_iter(coord_t x, coord_t y);

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
            * \brief Scale a pixel value from to the [0:1] interval to the raw interval.
            * \param scaled_val The scaled value.
            * \return The raw (i.e., stored) value.
            */
            typename MemImageViewBase<T>::channel_storage_t scale_px(channel_t scaled_val) const;

    }; // template class MemImageViewW

} // namespace phtr

#include "mem_image_view_w.tpl.h"

#endif // __MEM_IMAGE_VIEW_W_H__
