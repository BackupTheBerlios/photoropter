#ifndef __BASIC_IMAGE_IMPL_H__
#define __BASIC_IMAGE_IMPL_H__

#include "storagetypes.h"

namespace phtr
{

    class basic_image_impl
    {
        // construction, destruction
    protected:
        basic_image_impl();
    protected:
        basic_image_impl(const basic_image_impl& orig);
    public:
        virtual ~basic_image_impl();

        static basic_image_impl* create(storage::type ty, size_t width, size_t height);

        virtual storage::type storage_type() const = 0;

        // disable assignment
    protected:
        basic_image_impl& operator=(const basic_image_impl& orig);
    }; // class basic_image_impl

} // namespace phtr

#endif // __BASIC_IMAGE_IMPL_H__
