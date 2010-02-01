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
    MemImageViewW<T>::MemImageViewW(void* base_addr,
                                    coord_t width,
                                    coord_t height)
            : MemImageViewBase<T>(base_addr, width, height),
            roi_x_min_(0),
            roi_x_max_(width - 1),
            roi_y_min_(0),
            roi_y_max_(height - 1)
    {
        //NIL
    }

    template <Storage::type T>
    MemImageViewW<T>::~MemImageViewW()
    {
        //NIL
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_r(coord_t x, coord_t y, channel_t val)
    {
        this->base_addr_[this->get_px_offs(x,y) + this->r_offs_] = scale_px(val);
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_g(coord_t x, coord_t y, channel_t val)
    {
        this->base_addr_[this->get_px_offs(x,y) + this->g_offs_] = scale_px(val);
    }

    template <Storage::type T>
    void MemImageViewW<T>::write_px_val_b(coord_t x, coord_t y, channel_t val)
    {
        this->base_addr_[this->get_px_offs(x,y) + this->b_offs_] = scale_px(val);
    }

    template <Storage::type T>
    typename MemImageViewBase<T>::channel_storage_t MemImageViewW<T>::scale_px(channel_t scaled_val) const
    {
        return static_cast<typename MemImageViewBase<T>::channel_storage_t>(
                   ((static_cast<phtr::channel_t>(this->max_chan_val_)
                     - static_cast<phtr::channel_t>(this->min_chan_val_)) * scaled_val)
                   + static_cast<phtr::channel_t>(this->min_chan_val_)
               );
    }

    template <Storage::type T>
    typename MemImageViewW<T>::iter_t* MemImageViewW<T>::get_iter(coord_t x, coord_t y)
    {
        return new MemImageViewIterW<T>(this->width_,
                                        this->height_,
                                        this->base_addr_ + this->get_px_offs(x, y));
    }

    template <Storage::type T>
    void MemImageViewW<T>::set_roi(coord_t x_min, coord_t y_min, coord_t x_max, coord_t y_max)
    {
        roi_x_min_ = x_min;
        roi_x_max_ = x_max;
        roi_y_min_ = y_min;
        roi_y_max_ = y_max;
    }

    template <Storage::type T>
    void MemImageViewW<T>::get_roi(coord_t& x_min, coord_t& y_min, coord_t& x_max, coord_t& y_max)
    {
        x_min = roi_x_min_;
        x_max = roi_x_max_;
        y_min = roi_y_min_;
        y_max = roi_y_max_;
    }


} // namespace phtr