#include "mem_image_view_r.h"

namespace phtr
{

    MemImageViewR::MemImageViewR(const MemImageViewR::channel_storage_t* base_addr,
                                 size_t width,
                                 size_t height)
            : storage_info(width, height),
            base_addr_(base_addr),
            width_(width),
            height_(height),
            min_chan_val_(storage_info.min_val),
            max_chan_val_(storage_info.min_val),
            step_(storage_info.step),
            r_offs_(storage_info.r_offs),
            g_offs_(storage_info.g_offs),
            b_offs_(storage_info.b_offs)
    {
        //NIL
    }

    MemImageViewR::~MemImageViewR()
    {
        //NIL
    }

    coord_t MemImageViewR::width() const
    {
        return width_;
    }

    coord_t MemImageViewR::height() const
    {
        return height_;
    }

    channel_t MemImageViewR::get_px_val_r(coord_t x, coord_t y) const
    {
        return *(get_px_addr(x, y) + r_offs_);
    }

    channel_t MemImageViewR::get_px_val_g(coord_t x, coord_t y) const
    {
        return *(get_px_addr(x, y) + g_offs_);
    }

    channel_t MemImageViewR::get_px_val_b(coord_t x, coord_t y) const
    {
        return *(get_px_addr(x, y) + b_offs_);
    }

    const MemImageViewR::channel_storage_t*
    MemImageViewR::get_px_addr(coord_t x, coord_t y) const
    {
        return base_addr_ + (((y * width_) + x) * step_);
    }

} // namespace phtr
