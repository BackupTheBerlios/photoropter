#ifndef __MEM_IMAGE_VIEW_BASE_H__
#define __MEM_IMAGE_VIEW_BASE_H__

#include "storage_type.h"
#include "image_view.h"
#include "mem_storage_info.h"

namespace phtr
{

    /**
    * \brief Class template implementing a (reading) 'image view' of a given
    *  memory position.
    * \details The template uses internal templates to deal efficiently with
    * different storage types.
    */
    template <Storage::type T>
    class MemImageViewBase : public virtual IImageViewBase
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief The type of the internal storage info object.
            */
            typedef typename phtr::MemStorageInfo<T> storage_info_t;

        public:
            /**
            * \brief The channel storage type for this image (e.g., uint8_t).
            */
            typedef typename storage_info_t::channel_storage_t channel_storage_t;

        public:
            /**
            * \brief Constructor.
            * \param base_addr The base address of the image data in memory.
            * \param width The image width.
            * \param height The image height.
            */
            MemImageViewBase(void* base_addr,
                             coord_t width,
                             coord_t height);

        public:
            /**
            * \brief Desctructor.
            */
            virtual ~MemImageViewBase();

        public:
            /**
            * \brief Get the image width.
            * \return The width.
            */
            virtual coord_t width() const;

        public:
            /**
            * \brief Get the image height.
            * \return The height.
            */
            virtual coord_t height() const;

            /* ****************************************
             * internals
             * **************************************** */

        protected:
            /**
            * \brief Determine the 'pixel offset' to a given set of coordinates.
            * \param x The x coordinate.
            * \param y The y coordinate.
            * \return The offset
            */
            size_t get_px_offs(coord_t x, coord_t y) const;

        protected:
            /**
            * \brief The storage type of the image.
            */
            const Storage::type storage_type_;

        protected:
            /**
            * \brief Internal storage info object, used to calculate the memory
            * layout parameters.
            */
            const storage_info_t storage_info_;

        protected:
            /**
            * \brief The base address of the image.
            */
            channel_storage_t* base_addr_;

        protected:
            /**
            * \brief The image width.
            */
            const coord_t width_;

        protected:
            /**
            * \brief The image height.
            */
            const coord_t height_;

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

        protected:
            /**
            * \brief The distance between two adjacent pixels, in multiples
            * of the channel storage unit.
            */
            const size_t step_;

        protected:
            /**
            * \brief The offset of the red channel to the current memory position.
            */
            const size_t r_offs_;

        protected:
            /**
            * \brief The offset of the green channel to the current memory position.
            */
            const size_t g_offs_;

        protected:
            /**
            * \brief The offset of the blue channel to the current memory position.
            */
            const size_t b_offs_;

    }; // template class MemImageViewBase

} // namespace phtr

#include "mem_image_view_base.tpl.h"

#endif // __MEM_IMAGE_VIEW_BASE_H__
