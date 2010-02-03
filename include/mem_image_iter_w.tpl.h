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
    MemImageIterW<T>::MemImageIterW
    (channel_storage_t* base_addr, size_t px_offs, size_t step, size_t line_step,
     size_t r_offs, size_t g_offs, size_t b_offs)
            : MemImageIterBase<T>(base_addr, px_offs, step, line_step, r_offs, g_offs, b_offs)
    {
        //NIL
    }

    template <Storage::type T>
    void
    MemImageIterW<T>::write_px_val_r
    (channel_storage_t val)
    {
        this->base_addr_[this->px_offs_ + this->r_offs_] = val;
    }

    template <Storage::type T>
    void
    MemImageIterW<T>::write_px_val_g
    (channel_storage_t val)
    {
        this->base_addr_[this->px_offs_ + this->g_offs_] = val;
    }

    template <Storage::type T>
    void
    MemImageIterW<T>::write_px_val_b
    (channel_storage_t val)
    {
        this->base_addr_[this->px_offs_ + this->b_offs_] = val;
    }

    template <Storage::type T>
    void
    MemImageIterW<T>::write_px_val
    (Channel::type chan, channel_storage_t val)
    {
        switch (chan)
        {
            case Channel::red:
                write_px_val_r(val);
                break;

            case Channel::green:
                write_px_val_g(val);
                break;

            case Channel::blue:
            default:
                write_px_val_b(val);
                break;
        }
    }

} // namespace phtr
