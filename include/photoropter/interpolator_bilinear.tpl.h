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

    template <typename view_T>
    InterpolatorBilinear<view_T>::InterpolatorBilinear
    (const view_T& image_view)
            : InterpolatorBase<view_T>(image_view)
    {
    }

    template <typename view_T>
    InterpolatorBilinear<view_T>::InterpolatorBilinear
    (const view_T& image_view, interp_coord_t aspect_ratio)
            : InterpolatorBase<view_T>(image_view, aspect_ratio)
    {
    }

    template <typename view_T>
    interp_channel_t
    InterpolatorBilinear<view_T>::
    get_px_val
    (Channel::type chan, interp_coord_t x, interp_coord_t y) const
    {
        interp_coord_t x_scaled = (x + this->aspect_ratio_) * this->scale_x_;
        interp_coord_t y_scaled = (y + 1.0) * this->scale_y_;

        if ((x_scaled < 0) || (x_scaled > this->width_)
                || (y_scaled < 0) || (y_scaled > this->height_))
        {
            return this->null_val_;
        }

        // determine the edges of the 'square' in which we interpolate
        interp_coord_t x_1 = std::floor(x_scaled);
        interp_coord_t y_1 = std::floor(y_scaled);
        interp_coord_t x_2 = x_1 + 1;
        interp_coord_t y_2 = y_1 + 1;

        typename view_T::iter_t iter(
            this->image_view_.get_iter(
                static_cast<coord_t>(x_1), static_cast<coord_t>(y_1)));

        /* edge values
        val_11 == val(x1, y1) -> upper left
        val_21 == val(x2, y1) -> upper right
        val_12 == val(x1, y2) -> lower left
        val_22 == val(x2, y2) -> lower right
        */
        interp_channel_t val_11(iter.get_px_val(chan));
        interp_channel_t val_21(0);
        interp_channel_t val_12(0);
        interp_channel_t val_22(0);

        if (x_2 >= this->width_) // right image edge
        {
            val_21 = val_11;
        }
        else
        {
            iter.inc_x();
            val_21 = iter.get_px_val(chan);
            iter.dec_x();
        }

        if (y_2 >= this->height_) // lower edge
        {
            val_12 = val_11;
            val_22 = val_21;
        }
        else
        {
            iter.inc_y();
            val_12 = iter.get_px_val(chan);

            if (x_2 < this->width_)
            {
                iter.inc_x();
                val_22 = iter.get_px_val(chan);
            }
            else
            {
                val_22 = val_12;
            }
        }

        // interpolate in x direction
        interp_channel_t tmp_val_1 = (x_2 - x_scaled) * val_11 + (x_scaled - x_1) * val_21;
        interp_channel_t tmp_val_2 = (x_2 - x_scaled) * val_12 + (x_scaled - x_1) * val_22;

        // interpolate in y direction
        interp_channel_t interp_val = (y_2 - y_scaled) * tmp_val_1 + (y_scaled - y_1) * tmp_val_2;

        return interp_val;
    }

    template <typename view_T> template <typename coord_tuple_T>
    typename coord_tuple_T::channel_order_t::colour_tuple_t
    InterpolatorBilinear<view_T>::
    get_px_vals(const coord_tuple_T& coords) const
    {
        typedef typename coord_tuple_T::channel_order_t::colour_tuple_t colour_tuple_t;

        colour_tuple_t ret;

        for (size_t i = 0; i < colour_tuple_t::num_vals; ++i)
        {
            ret.value[i] = get_px_val(coord_tuple_T::channel_order_t::channel_type[i], coords.x[i], coords.y[i]);
        }

        return ret;
    }

} // namespace phtr
