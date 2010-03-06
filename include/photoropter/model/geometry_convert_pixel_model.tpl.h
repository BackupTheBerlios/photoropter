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

#include <photoropter/model/geometry_convert_pixel_model.h>

namespace phtr
{

    namespace model
    {

        /* ****************************************
        * GeometryConvertPixelModel
        * **************************************** */

        template <typename src_model_T, typename dst_model_T>
        GeometryConvertPixelModel<src_model_T, dst_model_T>::
        GeometryConvertPixelModel(double input_aspect, double input_crop)
                : CorrectionModelBase(1.5, input_aspect, 1.0, input_crop)
        {
            x0_ = 0.0;
            y0_ = 0.0;
            calc_coord_fact();
        }

        template <typename src_model_T, typename dst_model_T>
        void
        GeometryConvertPixelModel<src_model_T, dst_model_T>::
        set_focal_lengths(double src_focal_length, double dst_focal_length)
        {
            src_geom_.set_focal_length(src_focal_length);
            dst_geom_.set_focal_length(dst_focal_length);
        }

        template <typename src_model_T, typename dst_model_T>
        void
        GeometryConvertPixelModel<src_model_T, dst_model_T>::
        set_centre_shift(interp_coord_t x0, interp_coord_t y0)
        {
            x0_ = x0;
            y0_ = y0;
        }

        template <typename src_model_T, typename dst_model_T>
        void
        GeometryConvertPixelModel<src_model_T, dst_model_T>::
        get_centre_shift(interp_coord_t& x0, interp_coord_t& y0) const
        {
            x0 = x0_;
            y0 = y0_;
        }

        template <typename src_model_T, typename dst_model_T>
        void
        GeometryConvertPixelModel<src_model_T, dst_model_T>::
        get_src_coords(mem::CoordTupleMono& coords) const
        {
            typedef mem::CoordTupleMono::channel_order_t channel_order_t;
            typedef channel_order_t::colour_tuple_t colour_tuple_t;

            double x = (coords.x[0] - x0_) * coord_fact_;
            double y = (coords.y[0] - y0_) * coord_fact_;
            double phi(0.0);
            double theta(0.0);

            bool success = dst_geom_.to_spherical_coords(x, y, phi, theta)
                           && src_geom_.to_cartesian_coords(phi, theta, x, y);

            if (success)
            {
                coords.x[0] = (x / coord_fact_) + x0_;
                coords.y[0] = (y / coord_fact_) + y0_;
            }
            else
            {
                // set to illegal coordinates (i.e., outside the image area)
                coords.x[0] = -2.0 * input_aspect_;
                coords.y[0] = -2.0;
            }
        }

        template <typename src_model_T, typename dst_model_T>
        GeometryConvertPixelModel<src_model_T, dst_model_T>*
        GeometryConvertPixelModel<src_model_T, dst_model_T>::
        clone() const
        {
            return new GeometryConvertPixelModel(*this);
        }

        template <typename src_model_T, typename dst_model_T>
        void
        GeometryConvertPixelModel<src_model_T, dst_model_T>::
        calc_coord_fact()
        {
            CorrectionModelBase::calc_coord_fact();

            // correct the factor by
            // 24mm/2 == 12mm
            // (== half the height of a 35mm full-frame image)
            coord_fact_ *= 12;
        }

        template <typename src_geom_T>
        IGeometryConvertPixelModel* do_get_geometry_conversion(Geometry::type dst_geom,
                double input_aspect,
                double input_crop)
        {
            switch (dst_geom)
            {
                case Geometry::rectilinear:
                default:
                    return new GeometryConvertPixelModel<src_geom_T, geom::Rectilinear>(input_aspect, input_crop);

                case Geometry::fisheye_equidist:
                    return new GeometryConvertPixelModel<src_geom_T, geom::FisheyeEquidist>(input_aspect, input_crop);

                case Geometry::fisheye_equisolid:
                    return new GeometryConvertPixelModel<src_geom_T, geom::FisheyeEquisolid>(input_aspect, input_crop);

                case Geometry::fisheye_stereo:
                    return new GeometryConvertPixelModel<src_geom_T, geom::FisheyeStereo>(input_aspect, input_crop);

                case Geometry::fisheye_ortho:
                    return new GeometryConvertPixelModel<src_geom_T, geom::FisheyeOrtho>(input_aspect, input_crop);
            }
        }

    } // namespace phtr::model

} // namespace phtr
