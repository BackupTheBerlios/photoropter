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
    MemImageIterBase<T>::MemImageIterBase
    (channel_storage_t* base_addr, size_t px_offs,
     size_t step, size_t line_step,
     size_t r_offs, size_t g_offs, size_t b_offs)
            : base_addr_(base_addr),
            px_offs_(px_offs),
            storage_type_(T),
            step_(step),
            line_step_(line_step),
            r_offs_(r_offs),
            g_offs_(g_offs),
            b_offs_(b_offs)
    {
        //NIL
    }

    template <mem::Storage::type T>
    void
    MemImageIterBase<T>::inc_x
    ()
    {
        px_offs_ += step_;
    }

    template <mem::Storage::type T>
    void
    MemImageIterBase<T>::dec_x
    ()
    {
        px_offs_ -= step_;
    }

    template <mem::Storage::type T>
    void
    MemImageIterBase<T>::inc_y
    ()
    {
        px_offs_ += line_step_;
    }

    template <mem::Storage::type T>
    void
    MemImageIterBase<T>::dec_y
    ()
    {
        px_offs_ -= line_step_;
    }

    template <mem::Storage::type T>
    void
    MemImageIterBase<T>::set_px_offs(size_t px_offs)
    {
        px_offs_ = px_offs;
    }

} // namespace phtr
