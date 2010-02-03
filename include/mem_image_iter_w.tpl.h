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
    (coord_t width, coord_t height, channel_storage_t* addr)
            : MemImageIterBase<T>(width, height, addr)
    {
        //NIL
    }

    template <Storage::type T>
    void
    MemImageIterW<T>::write_px_val_r
    (channel_storage_t val)
    {
        this->addr_[this->r_offs_] = val;
    }

    template <Storage::type T>
    void
    MemImageIterW<T>::write_px_val_g
    (channel_storage_t val)
    {
        this->addr_[this->g_offs_] = val;
    }

    template <Storage::type T>
    void
    MemImageIterW<T>::write_px_val_b
    (channel_storage_t val)
    {
        this->addr_[this->b_offs_] = val;
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
