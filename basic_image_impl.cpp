#include <cstddef>

#include "basic_image_impl.h"
#include "image_impl.h"
#include "exception.h"

namespace phr
{

    basic_image_impl::basic_image_impl()
    {
        //ctor
    }

    basic_image_impl::~basic_image_impl()
    {
        //dtor
    }

    basic_image_impl* basic_image_impl::create(storage::type ty, size_t width, size_t height)
    {
        switch (ty)
        {
        case storage::rgb_8_inter:
            return new image_impl<storage::rgb_8_inter>(width, height);
            break;
        case storage::rgba_8_inter:
            return new image_impl<storage::rgba_8_inter>(width, height);
            break;
        case storage::rgb_16_inter:
            return new image_impl<storage::rgb_16_inter>(width, height);
            break;
        case storage::rgba_16_inter:
            return new image_impl<storage::rgba_16_inter>(width, height);
            break;
        case storage::rgb_32_inter:
            return new image_impl<storage::rgb_32_inter>(width, height);
            break;
        case storage::rgba_32_inter:
            return new image_impl<storage::rgba_32_inter>(width, height);
            break;
        case storage::rgb_8_planar:
            return new image_impl<storage::rgb_8_planar>(width, height);
            break;
        case storage::rgba_8_planar:
            return new image_impl<storage::rgba_8_planar>(width, height);
            break;
        case storage::rgb_16_planar:
            return new image_impl<storage::rgb_16_planar>(width, height);
            break;
        case storage::rgba_16_planar:
            return new image_impl<storage::rgba_16_planar>(width, height);
            break;
        case storage::rgb_32_planar:
            return new image_impl<storage::rgb_32_planar>(width, height);
            break;
        case storage::rgba_32_planar:
            return new image_impl<storage::rgba_32_planar>(width, height);
            break;
        default:
            throw exception::not_implemented("unknown storage type");
        }
    }

} // namespace phr
