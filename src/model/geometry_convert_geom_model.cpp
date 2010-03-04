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

#include <photoropter/model/geometry_convert_geom_model.h>

namespace phtr
{

    namespace model
    {

        /* ****************************************
        * GeometryConvertGeomModel
        * **************************************** */

        GeometryConvertGeomModel::
        GeometryConvertGeomModel(double input_aspect, double input_crop)
            : CorrectionModelBase(1.5, input_aspect, 1.0, input_crop)
        {
            x0_ = 0.0;
            y0_ = 0.0;
        }

        void
        GeometryConvertGeomModel::
        set_focal_lengths(double src_focal_length, double dst_focal_length)
        {
            src_model_.set_focal_length(src_focal_length);
            dst_model_.set_focal_length(dst_focal_length);
        }

        void
        GeometryConvertGeomModel::
        set_centre_shift(interp_coord_t x0, interp_coord_t y0)
        {
            x0_ = x0;
            y0_ = y0;
        }

        void
        GeometryConvertGeomModel::
        get_centre_shift(interp_coord_t& x0, interp_coord_t& y0) const
        {
            x0 = x0_;
            y0 = y0_;
        }

        void
        GeometryConvertGeomModel::
        get_src_coords(mem::CoordTupleRGB& coords) const
        {
            get_src_coords_impl(coords);
        }

        void
        GeometryConvertGeomModel::
        get_src_coords(mem::CoordTupleRGBA& coords) const
        {
            get_src_coords_impl(coords);
        }

        IGeomCorrectionModel* GeometryConvertGeomModel::clone() const
        {
            return new GeometryConvertGeomModel(*this);
        }

        template <typename coord_tuple_T>
        void
        GeometryConvertGeomModel::
        get_src_coords_impl(coord_tuple_T& coords) const
        {
            typedef typename coord_tuple_T::channel_order_t channel_order_t;
            typedef typename channel_order_t::colour_tuple_t colour_tuple_t;

            for(size_t i = 0; i < colour_tuple_t::num_vals; ++i)
            {
                double x = (coords.x[i] - x0_) * coord_fact_;
                double y = (coords.y[i] - y0_) * coord_fact_;
                double phi(0.0);
                double theta(0.0);

                bool success = dst_model_.to_spherical_coords(x, y, phi, theta)
                               && src_model_.to_cartesian_coords(phi, theta, x, y);

                if(success)
                {
                    coords.x[i] = (x / coord_fact_) + x0_;
                    coords.y[i] = (y / coord_fact_) + y0_;
                }
                else
                {
                    // set to illegal coordinates (i.e., outside the image area)
                    coords.x[i] = -2.0 * input_aspect_;
                    coords.y[i] = -2.0;
                }
            }

        }

        void
        GeometryConvertGeomModel::
        calc_coord_fact()
        {
            CorrectionModelBase::calc_coord_fact();

            // correct the factor by
            // 24mm/2 == 12mm
            // (== half the height of a 35mm full-frame image)
            coord_fact_ *= 12;
        }

    } // namespace phtr::model

} // namespace phtr
