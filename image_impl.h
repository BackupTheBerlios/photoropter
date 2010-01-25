#ifndef __IMAGE_IMPL_H__
#define __IMAGE_IMPL_H__

#include "basic_image.h"
#include "basic_image_impl.h"
#include "storagetypes.h"
#include "gil_storagetypes.h"

namespace phtr
{

    template <storage::type ty>
    class image_impl: public basic_image_impl
    {
        // typedefs, public constants
    public:
        static const storage::type storage_type_ = ty;

    public:
        typedef typename gil_storage<ty>::type image_t;

        // construction, destruction
    protected:
        image_impl(size_t width, size_t height);

    public:
        virtual ~image_impl();

        // properties
    private:
        storage::type storage_type() const;

    private:
        image_t image_;

        friend class basic_image;
        friend class basic_image_impl;
    }; // template class image_impl

} // namespace phtr

#include "image_impl.hpp"

#endif // __IMAGE_IMPL_H__
