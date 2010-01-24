#ifndef __BASIC_IMAGE_H__
#define __BASIC_IMAGE_H__

#include "storagetypes.h"
#include "types.h"

namespace phr
{

    class basic_image_impl;

    class basic_image
    {
    public:
        explicit basic_image(storage::type ty, size_t width, size_t height);
        virtual ~basic_image();

        storage::type storage_type() const;
        size_t width() const;
        size_t height() const;

    protected:
        // disable copying and assignment
        basic_image(const basic_image& orig);
        basic_image& operator=(const basic_image& orig);

    private:
        // (hidden) implementation
        img_sptr_t impl_;

        storage::type storage_type_;
        size_t width_;
        size_t height_;
    };

} // namespace phr

#endif // __BASIC_IMAGE_H__
