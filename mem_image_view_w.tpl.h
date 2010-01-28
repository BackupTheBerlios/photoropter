namespace phtr
{

    template <Storage::type T>
    MemImageViewW<T>::MemImageViewW(void* base_addr,
                                    size_t width,
                                    size_t height)
            : storage_type_(T),
            storage_info_(width, height),
            base_addr_(static_cast<MemImageViewW::channel_storage_t*>(base_addr)),
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
    MemImageViewW<T>::~MemImageViewW()
    {
        //NIL
    }

    template <Storage::type T>
    coord_t MemImageViewW<T>::width() const
    {
        return width_;
    }

    template <Storage::type T>
    coord_t MemImageViewW<T>::height() const
    {
        return height_;
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_r(coord_t x, coord_t y, channel_t val)
    {
        base_addr_[get_px_offs(x,y) + r_offs_] = scale_px(val);
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_g(coord_t x, coord_t y, channel_t val)
    {
        base_addr_[get_px_offs(x,y) + g_offs_] = scale_px(val);
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_b(coord_t x, coord_t y, channel_t val)
    {
        base_addr_[get_px_offs(x,y) + b_offs_] = scale_px(val);
    }

    template <Storage::type T>
    size_t MemImageViewW<T>::get_px_offs(coord_t x, coord_t y) const
    {
        return ((y * width_) + x) * step_;
    }

    template <Storage::type T>
    typename MemImageViewW<T>::channel_storage_t MemImageViewW<T>::scale_px(channel_t scaled_val) const
    {
        return static_cast<channel_storage_t>(
                   ((static_cast<phtr::channel_t>(max_chan_val_)
                     - static_cast<phtr::channel_t>(min_chan_val_)) * scaled_val)
                   + static_cast<phtr::channel_t>(min_chan_val_)
               );
    }

    template <Storage::type T>
    IImageViewIterW* MemImageViewW<T>::get_iter(coord_t, coord_t)
    {
        // FIXME
        return 0;
    }

    template <Storage::type T>
    void MemImageViewW<T>::get_roi(coord_t& x_min, coord_t& y_min, coord_t& x_max, coord_t& y_max)
    {
        // FIXME
        x_min = 0;
        y_min = 0;
        x_max = 0;
        y_max = 0;
    }


} // namespace phtr
