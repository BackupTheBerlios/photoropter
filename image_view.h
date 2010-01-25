#ifndef __IMAGE_VIEW_H__
#define __IMAGE_VIEW_H__

#include <cstddef>
#include <memory>

#include "types.h"

namespace phtr
{

    /**
    * \brief Basic image view interface.
    */

    class IImageViewBase
    {

        protected:
            /**
            * \brief Destructor.
            * Declared 'virtual' for proper polymorphic behaviour.
            */
            virtual ~IImageViewBase()
            {
                // nil
            }

        public:
            /**
            * \brief Get the image width.
            * \return The width.
            */
            virtual size_t width() const = 0;

        public:
            /**
            * \brief Get the image height.
            * \return The height.
            */
            virtual size_t height() const = 0;

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
            virtual channel_t get_px_val (channel::type chan, coord_t x, coord_t y) const = 0;

    }; // class IImageViewR

    /**
    * \brief Iterator class for write access to an image.
    * This class is used to implement fast linewise access to an image.
    */

    class IImageViewIterW
    {

        protected:
            /**
            * \brief Destructor.
            * Declared 'virtual' for proper polymorphic behaviour.
            */
            virtual ~IImageViewIterW()
            {
                // nil
            }

            /**
            * \brief Write a channel value.
            * \param chan The channel.
            * \param val  The value.
            */

        public:
            virtual void write_px_val (channel::type chan, channel_t val) = 0;

            /**
            * \brief Increment the current position.
            * \attention Boundary checks are not guaranteed.
            */

        public:
            virtual void inc_pos();

    }; // class IImageViewIterW

    /**
    * \brief Image view interface for writing of data.
    * Both direct pixel access and iterator-style access
    * for increased performance are defined.
    */

    class IImageViewW : public virtual IImageViewBase
    {

        public:
            /**
            * \brief Write a channel value directly to a pixel.
            * \param chan The channel.
            * \param x    The x coordinate.
            * \param y    The y coordinate.
            * \param val  The value.
            */
            virtual void write_px_val (channel::type chan, coord_t x, coord_t y, channel_t val) = 0;

            /**
            * \brief Get a pixel iterator.
            * A new iterator is instatiated and returned inside an auto_ptr object
            * (this is necessary since C++ does not support to return polymorphic
            * objects 'by value').
            * \return The iterator.
            */

        public:
            virtual std::auto_ptr<IImageViewIterW> get_iter (coord_t x, coord_t y) = 0;

    }; // class IImageViewW

} // namespace phtr

#endif // __IMAGE_VIEW_H__
