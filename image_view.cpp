#include "image_view.h"
#include "mem_image_view_r.h"

namespace phtr
{

    channel_t IImageViewR::get_px_val(Channel::type chan, coord_t x, coord_t y) const
    {
        switch (chan)
        {

            case Channel::red:
                return get_px_val_r(x, y);
                break;

            case Channel::green:
                return get_px_val_g(x, y);
                break;

            case Channel::blue:

            default:
                return get_px_val_b(x, y);
                break;
        }
    }

    IImageViewR* IImageViewR::get_mem_image_view_r(Storage::type storage_type,
            const void* base_addr,
            coord_t width,
            coord_t height)
    {
        switch (storage_type)
        {
            case Storage::rgb_8_inter:
                return new MemImageViewR<Storage::rgb_8_inter>(base_addr, width, height);
                break;

            case Storage::rgb_16_inter:
                return new MemImageViewR<Storage::rgb_16_inter>(base_addr, width, height);
                break;

            case Storage::rgb_32_inter:
                return new MemImageViewR<Storage::rgb_32_inter>(base_addr, width, height);
                break;

            case Storage::rgb_8_planar:
                return new MemImageViewR<Storage::rgb_8_planar>(base_addr, width, height);
                break;

            case Storage::rgb_16_planar:
                return new MemImageViewR<Storage::rgb_16_planar>(base_addr, width, height);
                break;

            case Storage::rgb_32_planar:
                return new MemImageViewR<Storage::rgb_32_planar>(base_addr, width, height);
                break;

            default:
                return 0;
                break;
        }
    }


} // namespace phtr
