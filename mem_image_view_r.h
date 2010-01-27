#ifndef __MEM_IMAGE_VIEW_R_H__
#define __MEM_IMAGE_VIEW_R_H__

#include "image_view.h"
#include "mem_storage_info.h"

#include <stdint.h>

namespace phtr
{

    /**
    * \brief Class template implementing an 'image view' of a given memory position.
    * \details The template uses internal templates to deal efficiently with different
    * storage types.
    */
    class MemImageViewR : public IImageViewR
    {

        private:
            /**
            * \brief The type of the internal storage info object.
            */
            typedef MemStorageInfo<Storage::rgb_8_inter> storage_info_t;

        private:
            /**
            * \brief The channel storage type (e.g., uint8_t).
            */
            typedef storage_info_t::channel_storage_t channel_storage_t;

        public:
            /**
            * \brief Constructor.
            * \param base_addr The base address of the image data in memory.
            * \param width The image width.
            * \param height The image height.
            */
            MemImageViewR(const channel_storage_t* base_addr,
                          coord_t width,
                          coord_t height);

        public:
            /**
            * \brief Desctructor.
            */
            virtual ~MemImageViewR();

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

        public:
            /**
            * \brief Read the 'red' channel value.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_r(coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the 'green' channel value.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_g(coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the 'blue' channel value.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_b(coord_t x, coord_t y) const;

        private:
            /**
            * \brief Determine the 'pixel address' to a given set of coordinates.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            */
            const channel_storage_t* get_px_addr(coord_t x, coord_t y) const;

        private:
            /**
            * \brief Internal storage info object, used to calculate the memory
            * layout parameters.
            */
            storage_info_t storage_info;

        private:
            /**
            * \brief The base address of the image.
            */
            const channel_storage_t* base_addr_;

        private:
            /**
            * \brief The image width.
            */
            const coord_t width_;

        private:
            /**
            * \brief The image height.
            */
            const coord_t height_;

        private:
            /**
            * \brief The minimal value a channel can hold.
            */
            const channel_storage_t min_chan_val_;

        private:
            /**
            * \brief The maximal value a channel can hold.
            */
            const channel_storage_t max_chan_val_;

        private:
            /**
            * \brief The distance between two adjacent pixels, in multiples
            * of the channel storage unit.
            */
            const size_t step_;

        private:
            /**
            * \brief The offset of the red channel to the current memory position.
            */
            const size_t r_offs_;

        private:
            /**
            * \brief The offset of the green channel to the current memory position.
            */
            const size_t g_offs_;

        private:
            /**
            * \brief The offset of the blue channel to the current memory position.
            */
            const size_t b_offs_;
    };

} // namespace phtr

#endif // __MEM_IMAGE_VIEW_R_H__
