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

    template <mem::Storage::type T>
    MemImageViewR<T>::
    MemImageViewR
    (const void* base_addr, coord_t width, coord_t height)
            : MemImageViewBase<T>(const_cast<void*>(base_addr), width, height)
    {
        aspect_ratio_ = static_cast<interp_coord_t>(this->width()) /
                        static_cast<interp_coord_t>(this->height());
    }

    template <mem::Storage::type T>
    typename MemImageViewR<T>::channel_storage_t
    MemImageViewR<T>::
    get_px_val_r
    (coord_t x, coord_t y) const
    {
        return this->base_addr_[this->get_px_offs(x, y) + this->r_offs_];
    }

    template <mem::Storage::type T>
    typename MemImageViewR<T>::channel_storage_t
    MemImageViewR<T>::
    get_px_val_g
    (coord_t x, coord_t y) const
    {
        return this->base_addr_[this->get_px_offs(x, y) + this->g_offs_];
    }

    template <mem::Storage::type T>
    typename MemImageViewR<T>::channel_storage_t
    MemImageViewR<T>::
    get_px_val_b
    (coord_t x, coord_t y) const
    {
        return this->base_addr_[this->get_px_offs(x, y) + this->b_offs_];
    }

    template <mem::Storage::type T>
    typename MemImageViewR<T>::channel_storage_t
    MemImageViewR<T>::
    get_px_val
    (Channel::type chan, coord_t x, coord_t y) const
    {
        switch (chan)
        {
            case Channel::red:
                return get_px_val_r(x, y);
                break;

            case Channel::green:
                return get_px_val_g(x, y);
                break;

            case Channel::blue:
            default:
                return get_px_val_b(x, y);
                break;
        }
    }

    template <mem::Storage::type T>
    typename MemImageViewR<T>::iter_t
    MemImageViewR<T>::
    get_iter
    (coord_t x, coord_t y) const
    {
        return MemImageIterR<T>(this->base_addr_, this->get_px_offs(x, y), this->step_, this->line_step_,
                                this->r_offs_, this->g_offs_, this->b_offs_);
    }

    template <mem::Storage::type T>
    void
    MemImageViewR<T>::set_aspect_ratio(interp_coord_t aspect_ratio)
    {
        aspect_ratio_ = aspect_ratio;
    }

    template <mem::Storage::type T>
    interp_coord_t
    MemImageViewR<T>::aspect_ratio() const
    {
        return aspect_ratio_;
    }

} // namespace phtr
