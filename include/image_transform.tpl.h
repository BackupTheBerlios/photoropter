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

    template <typename interpolator_t, typename image_view_w_t>
    ImageTransform<interpolator_t, image_view_w_t>::ImageTransform
    (const ImageTransform::image_view_t& image_view_r, image_view_w_t& image_view_w)
            : interpolator_(image_view_r),
            image_view_w_(image_view_w)
    {
        //NIL
    }

    template <typename interpolator_t, typename image_view_w_t>
    ImageTransform<interpolator_t, image_view_w_t>::~ImageTransform
    ()
    {
        //NIL
    }

    template <typename interpolator_t, typename image_view_w_t>
    void
    ImageTransform<interpolator_t, image_view_w_t>::do_transform
    ()
    {
        coord_t width = image_view_w_.width();
        coord_t height = image_view_w_.height();

        interp_coord_t scale_x = 1.0 / static_cast<interp_coord_t>(width - 1);
        interp_coord_t scale_y = 1.0 / static_cast<interp_coord_t>(height - 1);

        for (coord_t j = 0; j < height; ++j)
        {
            for (coord_t i = 0; i < width; ++i)
            {
                interp_coord_t x = (i * scale_x) - 0.5;
                interp_coord_t y = (j * scale_y) - 0.5;

                image_view_w_.write_px_val_r(i, j, interpolator_.get_px_val_r(x, y));
                image_view_w_.write_px_val_g(i, j, interpolator_.get_px_val_g(x, y));
                image_view_w_.write_px_val_b(i, j, interpolator_.get_px_val_b(x, y));
            }
        }
    }

} // namespace phtr
