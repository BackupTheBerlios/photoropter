#ifndef __IMAGE_VIEW_H__
#define __IMAGE_VIEW_H__

#include "types.h"
#include "channel_type.h"
#include "storage_type.h"

/**
* \brief Main namespace of the Photoropter library.
*/

namespace phtr
{

    /**
    * \brief Basic image view interface.
    */

    class IImageViewBase
    {

        protected:
            /**
            * \brief Constructor.
            */
            IImageViewBase()
            {
                //NIL
            }


        public:
            /**
            * \brief Destructor.
            * Declared 'virtual' for proper polymorphic behaviour.
            */
            virtual ~IImageViewBase()
            {
                //NIL
            }

        public:
            /**
            * \brief Get the image width.
            * \return The width.
            */
            virtual coord_t width() const = 0;

        public:
            /**
            * \brief Get the image height.
            * \return The height.
            */
            virtual coord_t height() const = 0;

    }; // class IImageViewBase

    /**
    * \brief Image view interface for reading of data.
    */

    class IImageViewR : public virtual IImageViewBase
    {

        public:
            /**
            * \brief Read a channel value.
            * \param chan The channel.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val(Channel::type chan, coord_t x, coord_t y) const;

        public:
            /**
            * \brief Read the 'red' channel value.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_r(coord_t x, coord_t y) const = 0;

        public:
            /**
            * \brief Read the 'green' channel value.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_g(coord_t x, coord_t y) const = 0;

        public:
            /**
            * \brief Read the 'blue' channel value.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \return The channel value.
            */
            virtual channel_t get_px_val_b(coord_t x, coord_t y) const = 0;

    }; // class IImageViewR

    /**
    * \brief Iterator class for write access to an image.
    * This class is used to implement fast linewise access to an image.
    */

    class IImageViewIterW
    {

        protected:
            /**
            * \brief Constructor.
            */
            IImageViewIterW()
            {
                //NIL
            }

        public:
            /**
            * \brief Destructor.
            * Declared 'virtual' for proper polymorphic behaviour.
            */
            virtual ~IImageViewIterW()
            {
                //NIL
            }

        public:
            /**
            * \brief Write a channel value to the current pixel.
            * \param chan The channel.
            * \param val  The value.
            */
            virtual void write_px_val(Channel::type chan, channel_t val) = 0;

        public:
            /**
            * \brief Increment the current position.
            * \attention Boundary checks are not guaranteed.
            */
            virtual void inc_pos();

    }; // class IImageViewIterW

    /**
    * \brief Image view interface for writing of data.
    * Both direct pixel access and iterator-style access
    * for increased performance are defined.
    */

    class IImageViewW : public virtual IImageViewBase
    {

        protected:
            /**
            * \brief Constructor.
            */
            IImageViewW()
            {
                //NIL
            }

        public:
            /**
            * \brief Write a channel value directly to a pixel.
            * \param chan The channel.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \param val  The value.
            */
            virtual void write_px_val(Channel::type chan, coord_t x, coord_t y, channel_t val);

        public:
            /**
            * \brief Write the 'red' channel value directly to a pixel.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \param val  The value.
            */
            virtual void write_px_val_r(coord_t x, coord_t y, channel_t val) = 0;

        public:
            /**
            * \brief Write the 'green' channel value directly to a pixel.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \param val  The value.
            */
            virtual void write_px_val_g(coord_t x, coord_t y, channel_t val) = 0;

        public:
            /**
            * \brief Write the 'blue' channel value directly to a pixel.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \param val  The value.
            */
            virtual void write_px_val_b(coord_t x, coord_t y, channel_t val) = 0;

        public:
            /**
            * \brief Get a pixel iterator.
            * A new iterator is instatiated and a pointer to it is returned
            * (this is necessary since C++ does not support to return polymorphic
            * objects 'by value').
            * \return The iterator.
            */
            virtual IImageViewIterW* get_iter(coord_t x, coord_t y) = 0;

        public:
            /**
            * \brief Get the current region of interest.
            * \param x_min The minimal x coordinate.
            * \param y_min The minimal y coordinate.
            * \param x_max The maximal x coordinate.
            * \param y_max The maximal y coordinate.
            */
            virtual void get_roi(coord_t& x_min, coord_t& y_min, coord_t& x_max, coord_t& y_max) = 0;

    }; // class IImageViewW

    /**
    * \brief Factory class to create image views.
    */
    class ImageViewFactory
    {

        public:
            /**
            * \brief Create a new @ref MemImageViewR instance.
            * \param storage_type The storage type.
            * \param base_addr    The buffer address.
            * \param width        The image width.
            * \param height       The image height.
            */
            static IImageViewR* get_mem_image_view_r(Storage::type storage_type,
                    const void* base_addr,
                    coord_t width,
                    coord_t height);

        public:
            /**
            * \brief Create a new @ref MemImageViewW instance.
            * \param storage_type The storage type.
            * \param base_addr    The buffer address.
            * \param width        The image width.
            * \param height       The image height.
            */
            static IImageViewW* get_mem_image_view_w(Storage::type storage_type,
                    void* base_addr,
                    coord_t width,
                    coord_t height);

    }; // class ImageViewFactory

} // namespace phtr

#endif // __IMAGE_VIEW_H__
