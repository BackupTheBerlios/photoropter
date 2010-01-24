#include "basic_image.h"
#include "image_impl.h"

namespace phr
{

    basic_image::basic_image(storage::type ty, size_t width, size_t height)
            :
            impl_(basic_image_impl::create(ty, width, height)),
            width_(width),
            height_(height)
    {
        //ctor
    }

    basic_image::~basic_image()
    {
        //dtor
    }

    storage::type basic_image::storage_type() const
    {
        return storage_type_;
    }

    size_t basic_image::width() const
    {
        return width_;
    }

    size_t basic_image::height() const
    {
        return height_;
    }

} // namespace phr
