/*

Photoropter: lens correction for digital cameras

Copyright (c) 2010 Robert Fendt

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

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
