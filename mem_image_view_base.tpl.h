namespace phtr
{

    template <Storage::type T>
    MemImageViewBase<T>::MemImageViewBase(void* base_addr,
                                          size_t width,
                                          size_t height)
            : storage_type_(T),
            storage_info_(width, height),
            base_addr_(static_cast<MemImageViewBase::channel_storage_t*>(base_addr)),
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
    MemImageViewBase<T>::~MemImageViewBase()
    {
        //NIL
    }

    template <Storage::type T>
    coord_t MemImageViewBase<T>::width() const
    {
        return width_;
    }

    template <Storage::type T>
    coord_t MemImageViewBase<T>::height() const
    {
        return height_;
    }

    template <Storage::type T>
    inline
    size_t MemImageViewBase<T>::get_px_offs(coord_t x, coord_t y) const
    {
        return ((y * width_) + x) * step_;
    }


} // namespace phtr
