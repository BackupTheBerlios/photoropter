#include "mem_image_view_r.h"

namespace phtr
{

    MemImageViewR::MemImageViewR (const MemImageViewR::channel_storage_t* base_addr,
                                  size_t width,
                                  size_t height)
            : storage_info (width, height),
            base_addr_ (base_addr),
            width_ (width),
            height_ (height),
            min_chan_val_ (storage_info.min_val),
            max_chan_val_ (storage_info.min_val),
            step_ (storage_info.step),
            r_offs_ (storage_info.r_offs),
            g_offs_ (storage_info.g_offs),
            b_offs_ (storage_info.b_offs)
    {
        //ctor
    }

    MemImageViewR::~MemImageViewR()
    {
        //dtor
    }

} // namespace phtr
