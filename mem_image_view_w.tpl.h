namespace phtr
{

    template <Storage::type T>
    MemImageViewW<T>::MemImageViewW(void* base_addr,
                                    size_t width,
                                    size_t height)
            : MemImageViewBase<T>(base_addr, width, height)
    {
        //NIL
    }

    template <Storage::type T>
    MemImageViewW<T>::~MemImageViewW()
    {
        //NIL
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_r(coord_t x, coord_t y, channel_t val)
    {
        this->base_addr_[this->get_px_offs(x,y) + this->r_offs_] = scale_px(val);
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_g(coord_t x, coord_t y, channel_t val)
    {
        this->base_addr_[this->get_px_offs(x,y) + this->g_offs_] = scale_px(val);
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_b(coord_t x, coord_t y, channel_t val)
    {
        this->base_addr_[this->get_px_offs(x,y) + this->b_offs_] = scale_px(val);
    }

    template <Storage::type T>
    typename MemImageViewBase<T>::channel_storage_t MemImageViewW<T>::scale_px(channel_t scaled_val) const
    {
        return static_cast<typename MemImageViewBase<T>::channel_storage_t>(
                   ((static_cast<phtr::channel_t>(this->max_chan_val_)
                     - static_cast<phtr::channel_t>(this->min_chan_val_)) * scaled_val)
                   + static_cast<phtr::channel_t>(this->min_chan_val_)
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
