namespace phtr
{

    template <Storage::type T>
    MemImageViewR<T>::MemImageViewR(const void* base_addr,
                                    size_t width,
                                    size_t height)
            : storage_type_(T),
            storage_info_(width, height),
            base_addr_(static_cast<const MemImageViewR::channel_storage_t*>(base_addr)),
            width_(width),
            height_(height),
            min_chan_val_(storage_info_.min_val),
            max_chan_val_(storage_info_.max_val),
            step_(storage_info_.step),
            r_offs_(storage_info_.r_offs),
            g_offs_(storage_info_.g_offs),
            b_offs_(storage_info_.b_offs)
    {
        //NIL
    }

    template <Storage::type T>
    MemImageViewR<T>::~MemImageViewR()
    {
        //NIL
    }

    template <Storage::type T>
    coord_t MemImageViewR<T>::width() const
    {
        return width_;
    }

    template <Storage::type T>
    coord_t MemImageViewR<T>::height() const
    {
        return height_;
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::get_px_val_r(coord_t x, coord_t y) const
    {
        return scale_px(base_addr_[get_px_offs(x,y) + r_offs_]);
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::get_px_val_g(coord_t x, coord_t y) const
    {
        return scale_px(base_addr_[get_px_offs(x,y) + g_offs_]);
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::get_px_val_b(coord_t x, coord_t y) const
    {
        return scale_px(base_addr_[get_px_offs(x,y) + b_offs_]);
    }

    template <Storage::type T>
    size_t MemImageViewR<T>::get_px_offs(coord_t x, coord_t y) const
    {
        return ((y * width_) + x) * step_;
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::scale_px(channel_storage_t raw_val) const
    {
        return (static_cast<phtr::channel_t>(raw_val) - static_cast<phtr::channel_t>(min_chan_val_))
               / (static_cast<phtr::channel_t>(max_chan_val_) - static_cast<phtr::channel_t>(min_chan_val_));
    }


} // namespace phtr
