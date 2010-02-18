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
    MemImageViewW<T>::
    MemImageViewW
    (void* base_addr, coord_t width, coord_t height)
            : MemImageViewBase<T>(base_addr, width, height),
            roi_x_min_(0),
            roi_x_limit_(width),
            roi_y_min_(0),
            roi_y_limit_(height),
            parent_offs_x_(0),
            parent_offs_y_(0),
            parent_width_(width),
            parent_height_(height)
    {
        //NIL
    }

    template <mem::Storage::type T>
    void
    MemImageViewW<T>::
    write_px_val
    (Channel::type chan, coord_t x, coord_t y, channel_storage_t val)
    {
        switch (chan)
        {
            case Channel::red:
                this->base_addr_[this->get_px_offs(x, y) + this->r_offs_] = val;
                break;

            case Channel::green:
                this->base_addr_[this->get_px_offs(x, y) + this->g_offs_] = val;
                break;

            case Channel::blue:
            default:
                this->base_addr_[this->get_px_offs(x, y) + this->b_offs_] = val;
                break;
        }
    }

    template <mem::Storage::type T>
    void
    MemImageViewW<T>::
    write_px_vals
    (const mem::CoordTupleRGB& coords, const mem::ColourTupleRGB& values)
    {
        write_px_val(Channel::red,   coords.x_r, coords.y_r, values.val_r);
        write_px_val(Channel::green, coords.x_g, coords.y_g, values.val_g);
        write_px_val(Channel::blue,  coords.x_b, coords.y_b, values.val_b);
    }

    template <mem::Storage::type T>
    typename MemImageViewW<T>::iter_t
    MemImageViewW<T>::
    get_iter
    (coord_t x, coord_t y)
    {
        return MemImageIterW<T>(this->base_addr_, this->get_px_offs(x, y), this->step_, this->line_step_,
                                this->r_offs_, this->g_offs_, this->b_offs_);
    }

    template <mem::Storage::type T>
    void
    MemImageViewW<T>::
    set_roi
    (coord_t x_min, coord_t y_min, coord_t x_limit, coord_t y_limit)
    {
        roi_x_min_ = x_min;
        roi_x_limit_ = x_limit;
        roi_y_min_ = y_min;
        roi_y_limit_ = y_limit;
    }

    template <mem::Storage::type T>
    void
    MemImageViewW<T>::
    get_roi
    (coord_t& x_min, coord_t& y_min, coord_t& x_limit, coord_t& y_limit)
    {
        x_min = roi_x_min_;
        x_limit = roi_x_limit_;
        y_min = roi_y_min_;
        y_limit = roi_y_limit_;
    }

    template <mem::Storage::type T>
    void
    MemImageViewW<T>::
    set_parent_window(coord_t offs_x, coord_t offs_y,
                      coord_t width, coord_t height)
    {
        parent_offs_x_ = offs_x;
        parent_offs_y_ = offs_y;
        parent_width_ = width;
        parent_height_ = height;
    }

    template <mem::Storage::type T>
    void
    MemImageViewW<T>::
    get_parent_window(coord_t& offs_x, coord_t& offs_y,
                      coord_t& width, coord_t& height)
    {
        offs_x = parent_offs_x_;
        offs_y = parent_offs_y_;
        width = parent_width_;
        height = parent_height_;
    }

} // namespace phtr
