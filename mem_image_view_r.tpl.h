namespace phtr
{

    template <Storage::type T>
    MemImageViewR<T>::MemImageViewR(const void* base_addr,
                                    coord_t width,
                                    coord_t height)
            : MemImageViewBase<T>(const_cast<void*>(base_addr), width, height)
    {
        //NIL
    }

    template <Storage::type T>
    MemImageViewR<T>::~MemImageViewR()
    {
        //NIL
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::get_px_val_r(coord_t x, coord_t y) const
    {
        return scale_px(this->base_addr_[this->get_px_offs(x,y) + this->r_offs_]);
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::get_px_val_g(coord_t x, coord_t y) const
    {
        return scale_px(this->base_addr_[this->get_px_offs(x,y) + this->g_offs_]);
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::get_px_val_b(coord_t x, coord_t y) const
    {
        return scale_px(this->base_addr_[this->get_px_offs(x,y) + this->b_offs_]);
    }

    template <Storage::type T>
    channel_t MemImageViewR<T>::scale_px(typename MemImageViewBase<T>::channel_storage_t raw_val) const
    {
        return (static_cast<phtr::channel_t>(raw_val) - static_cast<phtr::channel_t>(this->min_chan_val_))
               / (static_cast<phtr::channel_t>(this->max_chan_val_) - static_cast<phtr::channel_t>(this->min_chan_val_));
    }


} // namespace phtr
