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

    ///@cond PROTECTED

    template <mem::Storage::type T>
    MemImageViewBase<T>::MemImageViewBase
    (void* base_addr, coord_t width, coord_t height)
        : storage_type_(T),
          storage_info_(width, height),
          base_addr_(static_cast<MemImageViewBase::channel_storage_t*>(base_addr)),
          width_(width),
          height_(height),
          min_chan_val_(storage_info_.min_val),
          max_chan_val_(storage_info_.max_val),
          step_(storage_info_.step),
          line_step_(storage_info_.line_step),
          r_offs_(storage_info_.r_offs),
          g_offs_(storage_info_.g_offs),
          b_offs_(storage_info_.b_offs),
          a_offs_(storage_info_.a_offs)
    {
        //NIL
    }

    template <mem::Storage::type T>
    coord_t
    MemImageViewBase<T>::width
    () const
    {
        return width_;
    }

    template <mem::Storage::type T>
    coord_t
    MemImageViewBase<T>::height()
    const
    {
        return height_;
    }

    template <mem::Storage::type T>
    inline size_t
    MemImageViewBase<T>::get_px_offs
    (coord_t x, coord_t y) const
    {
        return ((y * width_) + x) * step_;
    }

    ///@endcond

} // namespace phtr
