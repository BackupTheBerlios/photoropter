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
    MemImageViewW<storage_T>::
    MemImageViewW
    (void* base_addr, coord_t width, coord_t height)
        : MemImageViewBase<storage_T>(base_addr, width, height),
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

    template <mem::Storage::type storage_T>
    void
    MemImageViewW<storage_T>::
    write_px_val
    (Channel::type chan, coord_t x, coord_t y, channel_storage_t val)
    {
        switch(chan)
        {
            case Channel::red:
            default:
                this->base_addr_[this->get_px_offs(x, y) + this->r_offs_] = val;
                break;

            case Channel::green:
                this->base_addr_[this->get_px_offs(x, y) + this->g_offs_] = val;
                break;

            case Channel::blue:
                this->base_addr_[this->get_px_offs(x, y) + this->b_offs_] = val;
                break;

            case Channel::alpha:
                this->base_addr_[this->get_px_offs(x, y) + this->a_offs_] = val;
                break;
        }
    }

    template <mem::Storage::type storage_T> template <typename coord_tuple_T>
    void
    MemImageViewW<storage_T>::
    write_px_vals
    (const coord_tuple_T& coords, const typename coord_tuple_T::channel_order_t::colour_tuple_t& values)
    {
        typedef typename coord_tuple_T::channel_order_t channel_order_t;
        typedef typename channel_order_t::colour_tuple_t colour_tuple_t;

        for(size_t i = 0; i < colour_tuple_t::num_vals; ++i)
        {
            write_px_val(channel_order_t::channel_type[i], coords.x[i], coords.y[i],
                         static_cast<channel_storage_t>(values.value[i] + 0.5));
        }

    }

    template <mem::Storage::type storage_T>
    typename MemImageViewW<storage_T>::iter_t
    MemImageViewW<storage_T>::
    get_iter
    (coord_t x, coord_t y)
    {
        return MemImageIterW<storage_T>(this->base_addr_, this->get_px_offs(x, y), this->step_, this->line_step_,
                                        this->r_offs_, this->g_offs_, this->b_offs_, this->a_offs_);
    }

    template <mem::Storage::type storage_T>
    void
    MemImageViewW<storage_T>::
    set_roi
    (coord_t x_min, coord_t y_min, coord_t x_limit, coord_t y_limit)
    {
        roi_x_min_ = x_min;
        roi_x_limit_ = x_limit;
        roi_y_min_ = y_min;
        roi_y_limit_ = y_limit;
    }

    template <mem::Storage::type storage_T>
    void
    MemImageViewW<storage_T>::
    get_roi
    (coord_t& x_min, coord_t& y_min, coord_t& x_limit, coord_t& y_limit)
    {
        x_min = roi_x_min_;
        x_limit = roi_x_limit_;
        y_min = roi_y_min_;
        y_limit = roi_y_limit_;
    }

    template <mem::Storage::type storage_T>
    void
    MemImageViewW<storage_T>::
    set_parent_window(coord_t offs_x, coord_t offs_y,
                      coord_t width, coord_t height)
    {
        parent_offs_x_ = offs_x;
        parent_offs_y_ = offs_y;
        parent_width_ = width;
        parent_height_ = height;
    }

    template <mem::Storage::type storage_T>
    void
    MemImageViewW<storage_T>::
    get_parent_window(coord_t& offs_x, coord_t& offs_y,
                      coord_t& width, coord_t& height)
    {
        offs_x = parent_offs_x_;
        offs_y = parent_offs_y_;
        width = parent_width_;
        height = parent_height_;
    }

} // namespace phtr
