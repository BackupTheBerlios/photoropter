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