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

    template <mem::Storage::type storage_T>
    MemImageViewR<storage_T>::
    MemImageViewR
    (const void* base_addr, coord_t width, coord_t height)
        : MemImageViewBase<storage_T>(const_cast<void*>(base_addr), width, height)
    {
        aspect_ratio_ = static_cast<interp_coord_t>(this->width()) /
                        static_cast<interp_coord_t>(this->height());
    }

    template <mem::Storage::type storage_T>
    typename MemImageViewR<storage_T>::channel_storage_t
    MemImageViewR<storage_T>::
    get_px_val
    (Channel::type chan, coord_t x, coord_t y) const
    {
        switch(chan)
        {
            case Channel::red:
            default:
                return this->base_addr_[this->get_px_offs(x, y) + this->r_offs_];
                break;

            case Channel::green:
                return this->base_addr_[this->get_px_offs(x, y) + this->g_offs_];
                break;

            case Channel::blue:
                return this->base_addr_[this->get_px_offs(x, y) + this->b_offs_];
                break;

            case Channel::alpha:
                return this->base_addr_[this->get_px_offs(x, y) + this->a_offs_];
                break;
        }
    }

    template <mem::Storage::type storage_T>
    typename MemImageViewR<storage_T>::iter_t
    MemImageViewR<storage_T>::
    get_iter
    (coord_t x, coord_t y) const
    {
        return MemImageIterR<storage_T>(this->base_addr_, this->get_px_offs(x, y), this->step_, this->line_step_,
                                        this->r_offs_, this->g_offs_, this->b_offs_, this->a_offs_);
    }

    template <mem::Storage::type storage_T>
    void
    MemImageViewR<storage_T>::set_aspect_ratio(interp_coord_t aspect_ratio)
    {
        aspect_ratio_ = aspect_ratio;
    }

    template <mem::Storage::type storage_T>
    interp_coord_t
    MemImageViewR<storage_T>::aspect_ratio() const
    {
        return aspect_ratio_;
    }

} // namespace phtr
