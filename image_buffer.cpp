#include "image_buffer.h"
#include "image_buffer_impl.h"

namespace phtr
{
    IImageBuffer* IImageBuffer::get_image_buffer(phtr::Storage::type storage_type,
            coord_t width,
            coord_t height)
    {
        switch (storage_type)
        {
            case Storage::rgb_8_inter:
                return new ImageBufferImpl<Storage::rgb_8_inter>(width, height);
                break;

            case Storage::rgb_16_inter:
                return new ImageBufferImpl<Storage::rgb_16_inter>(width, height);
                break;

            case Storage::rgb_32_inter:
                return new ImageBufferImpl<Storage::rgb_32_inter>(width, height);
                break;

            case Storage::rgb_8_planar:
                return new ImageBufferImpl<Storage::rgb_8_planar>(width, height);
                break;

            case Storage::rgb_16_planar:
                return new ImageBufferImpl<Storage::rgb_16_planar>(width, height);
                break;

            case Storage::rgb_32_planar:
                return new ImageBufferImpl<Storage::rgb_32_planar>(width, height);
                break;

            case Storage::unknown:
            default:
                return 0;
        }

        return 0;
    }

} // namespace phtr
