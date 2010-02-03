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

#ifdef HAVE_OPENMP
#pragma omp parallel for
#endif
        for (coord_t j = 0; j < height; ++j)
        {

            typename image_view_w_t::iter_t iter(image_view_w_.get_iter(0, j));

            for (coord_t i = 0; i < width; ++i)
            {
                /* scale coordinates to get corresponding coordinates for
                the interpolator */
                interp_coord_t dst_x = (i * scale_x) - 0.5;
                interp_coord_t dst_y = (j * scale_y) - 0.5;

                // get coordinates transformed to source image
                interp_coord_t src_x_r(0);
                interp_coord_t src_y_r(0);
                interp_coord_t src_x_g(0);
                interp_coord_t src_y_g(0);
                interp_coord_t src_x_b(0);
                interp_coord_t src_y_b(0);
                get_source_coords(dst_x, dst_y,
                                  src_x_r, src_y_r,
                                  src_x_g, src_y_g,
                                  src_x_b, src_y_b);

                // get channel values
                typename image_view_w_t::iter_t::channel_storage_t
                val_r(interpolator_.get_px_val(Channel::red, src_x_r, src_y_r));
                typename image_view_w_t::iter_t::channel_storage_t
                val_g(interpolator_.get_px_val(Channel::green, src_x_g, src_y_g));
                typename image_view_w_t::iter_t::channel_storage_t
                val_b(interpolator_.get_px_val(Channel::blue, src_x_b, src_y_b));

                // write channel values
                iter.write_px_val(Channel::red, val_r);
                iter.write_px_val(Channel::green, val_g);
                iter.write_px_val(Channel::blue, val_b);

                // increment iterator position
                iter.inc_x();

            } // column loop

        } // line loop

    } //  ImageTransform<...>::do_transform()

    template <typename interpolator_t, typename image_view_w_t>
    void
    ImageTransform<interpolator_t, image_view_w_t>::get_source_coords(interp_coord_t dst_x, interp_coord_t dst_y,
            interp_coord_t& src_x_r, interp_coord_t& src_y_r,
            interp_coord_t& src_x_g, interp_coord_t& src_y_g,
            interp_coord_t& src_x_b, interp_coord_t& src_y_b)
    {
        src_x_r = dst_x;
        src_y_r = dst_y;

        src_x_g = dst_x;
        src_y_g = dst_y;

        src_x_b = dst_x;
        src_y_b = dst_y;
    }

} // namespace phtr
