namespace phtr
{

    template <phtr::Storage::type T>
    ImageBufferImpl<T>::ImageBufferImpl(coord_t width, coord_t height)
            : storage_info_(width, height),
            data_(0),
            width_(width),
            height_(height),
            num_channels_(storage_info_.num_channels)
    {
        num_pixels_ = width_ * height_;
        num_bytes_ = num_pixels_ * num_channels_ * sizeof(channel_storage_t);

        data_ = new channel_storage_t[num_pixels_ * num_channels_];
    }

    template <phtr::Storage::type T>
    ImageBufferImpl<T>::~ImageBufferImpl()
    {
        delete[] data_;
    }

    template <phtr::Storage::type T>
    void* ImageBufferImpl<T>::data()
    {
        return data_;
    }

    template <phtr::Storage::type T>
    size_t ImageBufferImpl<T>::num_pixels()
    {
        return num_pixels_;
    }

    template <phtr::Storage::type T>
    size_t ImageBufferImpl<T>::num_bytes()
    {
        return num_bytes_;
    }

} // namespace phtr
