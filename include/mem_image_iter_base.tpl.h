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
    MemImageIterBase<T>::MemImageIterBase
    (coord_t width, coord_t height, channel_storage_t* addr)
            : addr_(addr),
            storage_type_(T),
            step_(mem_layout_t::step(width, height)),
            line_step_(mem_layout_t::line_step(width, height)),
            r_offs_(mem_layout_t::r_offs(width, height)),
            g_offs_(mem_layout_t::g_offs(width, height)),
            b_offs_(mem_layout_t::b_offs(width, height)),
            min_chan_val_(ChannelRange<T>::min()),
            max_chan_val_(ChannelRange<T>::max())
    {
        //NIL
    }

    template <Storage::type T>
    MemImageIterBase<T>::~MemImageIterBase
    ()
    {
        //NIL
    }

    template <Storage::type T>
    void
    MemImageIterBase<T>::inc_x
    ()
    {
        addr_ += step_;
    }

    template <Storage::type T>
    void
    MemImageIterBase<T>::dec_x
    ()
    {
        addr_ -= step_;
    }

    template <Storage::type T>
    void
    MemImageIterBase<T>::inc_y
    ()
    {
        addr_ += line_step_;
    }

    template <Storage::type T>
    void
    MemImageIterBase<T>::dec_y
    ()
    {
        addr_ -= line_step_;
    }

} // namespace phtr
