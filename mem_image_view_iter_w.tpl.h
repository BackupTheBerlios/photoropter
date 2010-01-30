namespace phtr
{

    template <Storage::type T>
    MemImageViewIterW<T>::MemImageViewIterW(coord_t width, coord_t height, channel_storage_t* addr)
            : addr_(addr),
            storage_type_(T),
            step_(mem_layout_t::step(width, height)),
            r_offs_(mem_layout_t::r_offs(width, height)),
            g_offs_(mem_layout_t::g_offs(width, height)),
            b_offs_(mem_layout_t::b_offs(width, height))
    {
        //ctor
    }

    template <Storage::type T>
    MemImageViewIterW<T>::~MemImageViewIterW()
    {
        //dtor
    }

    template <Storage::type T>
    void MemImageViewIterW<T>::write_px_val_r(channel_t val)
    {
        addr_[r_offs_] = val;
    }

    template <Storage::type T>
    void MemImageViewIterW<T>::write_px_val_g(channel_t val)
    {
        addr_[g_offs_] = val;
    }

    template <Storage::type T>
    void MemImageViewIterW<T>::write_px_val_b(channel_t val)
    {
        addr_[b_offs_] = val;
    }

    template <Storage::type T>
    void MemImageViewIterW<T>::inc_pos()
    {
        addr_ += step_;
    }

} // namespace phtr
