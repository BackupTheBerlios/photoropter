#ifndef __IMAGE_BUFFER_H__
#define __IMAGE_BUFFER_H__

#include "types.h"
#include "storage_type.h"

namespace phtr
{
    /**
    * \brief Interface class representing a buffer for an image.
    */
    class IImageBuffer
    {

        protected:
            /**
            * \brief Constructor.
            */
            IImageBuffer()
            {
                //NIL
            }

        public:
            /**
            * \brief Destructor.
            * \note Declared 'virtual' for proper polymorphic behaviour.
            */
            virtual ~IImageBuffer()
            {
                //NIL
            }

        public:
            /**
            * \brief Return a pointer to the data the buffer holds.
            * \return Pointer to the data.
            */
            virtual void* data() = 0;

        public:
            /**
            * \brief Return the number of pixels the buffer can hold.
            * \return The number of pixels.
            */
            virtual size_t num_pixels() = 0;

        public:
            /**
            * \brief Return the number of bytes the buffer holds.
            * \return The number of bytes.
            */
            virtual size_t num_bytes() = 0;

        public:
            /**
            * \brief Get an image buffer instance.
            * \param storage_type The storage type (e.g., \ref Storage::rgb_8_inter).
            * \param width The image width.
            * \param height The image height.
            * \return Pointer to the buffer object.
            */
            static IImageBuffer* get_image_buffer(phtr::Storage::type storage_type,
                                                  coord_t width,
                                                  coord_t height);

    }; // class IImageBuffer

} // namespace phtr

#endif // __IMAGE_BUFFER_H__
