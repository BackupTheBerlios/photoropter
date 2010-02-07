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

    void GeomCorrectionQueue::get_source_coords(interp_coord_t dst_x, interp_coord_t dst_y,
            interp_coord_t& src_x_r, interp_coord_t& src_y_r,
            interp_coord_t& src_x_g, interp_coord_t& src_y_g,
            interp_coord_t& src_x_b, interp_coord_t& src_y_b) const
    {
        src_x_r = dst_x;
        src_y_r = dst_y;

        src_x_g = dst_x;
        src_y_g = dst_y;

        src_x_b = dst_x;
        src_y_b = dst_y;

        for (size_t i = 0; i < n_models_; ++i)
        {
            correction_model_[i]->get_src_coords(src_x_r, src_y_r, src_x_g, src_y_g, src_x_b, src_y_b);
        }

    }

} // namespace phtr
