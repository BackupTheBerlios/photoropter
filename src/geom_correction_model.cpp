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

#include <cmath>

#include <photoropter/colour_tuple.h>
#include <photoropter/mem_layout.h>
#include <photoropter/geom_correction_model.h>

namespace phtr
{

    namespace model
    {

        PTLensGeomModel::
        PTLensGeomModel(double param_aspect, double input_aspect,
                        double param_crop, double input_crop)
                : CorrectionModelBase(param_aspect, input_aspect, param_crop, input_crop),
                a_(0),
                b_(0),
                c_(0),
                d_(0),
                x0_(0),
                y0_(0)
        {
            //NIL
        }

        PTLensGeomModel::
        PTLensGeomModel(double input_aspect)
                : CorrectionModelBase(input_aspect),
                a_(0),
                b_(0),
                c_(0),
                d_(0),
                x0_(0),
                y0_(0)
        {
        }

        void
        PTLensGeomModel::
        set_model_params(double a, double b, double c, double d)
        {
            a_ = a * std::pow(coord_fact_, 3);
            b_ = b * std::pow(coord_fact_, 2);
            c_ = c * coord_fact_;
            d_ = d;
        }

        void
        PTLensGeomModel::
        set_model_params(double a, double b, double c)
        {
            a_ = a * std::pow(coord_fact_, 3);
            b_ = b * std::pow(coord_fact_, 2);
            c_ = c * coord_fact_;
            d_ = 1.0 - (a + b + c);
        }

        void
        PTLensGeomModel::
        get_model_params(double& a, double& b, double& c, double& d) const
        {
            a = a_ / std::pow(coord_fact_, 3);
            b = b_ / std::pow(coord_fact_, 2);
            c = c_ / coord_fact_;
            d = d_;
        }

        void
        PTLensGeomModel::
        set_centre_shift(interp_coord_t x0, interp_coord_t y0)
        {
            x0_ = x0;
            y0_ = y0;
        }

        void
        PTLensGeomModel::
        get_centre_shift(interp_coord_t& x0, interp_coord_t& y0) const
        {
            x0 = x0_;
            y0 = y0_;
        }

        void
        PTLensGeomModel::
        get_src_coords(mem::CoordTupleRGB& coords) const
        {
            typedef mem::ColourTupleRGB::channel_order_t channel_order_t;

            // calculate the 'red' channel
            coords.x[channel_order_t::idx_red] -= x0_;
            coords.y[channel_order_t::idx_red] -= y0_;
            double r_r = std::sqrt(coords.x[channel_order_t::idx_red] * coords.x[channel_order_t::idx_red] +
                                   coords.y[channel_order_t::idx_red] * coords.y[channel_order_t::idx_red]);
            double cos_phi_r = coords.x[channel_order_t::idx_red] / r_r;
            double sin_phi_r = coords.y[channel_order_t::idx_red] / r_r;
            r_r = (((a_ * r_r + b_) * r_r + c_) * r_r + d_) * r_r;

            coords.x[channel_order_t::idx_red] = cos_phi_r * r_r + x0_;
            coords.y[channel_order_t::idx_red] = sin_phi_r * r_r + y0_;

            // calculate the 'green' channel
            coords.x[channel_order_t::idx_green] -= x0_;
            coords.y[channel_order_t::idx_green] -= y0_;
            double r_g = std::sqrt(coords.x[channel_order_t::idx_green] * coords.x[channel_order_t::idx_green] +
                                   coords.y[channel_order_t::idx_green] * coords.y[channel_order_t::idx_green]);
            double cos_phi_g = coords.x[channel_order_t::idx_green] / r_g;
            double sin_phi_g = coords.y[channel_order_t::idx_green] / r_g;
            r_g = (((a_ * r_g + b_) * r_g + c_) * r_g + d_) * r_g;

            coords.x[channel_order_t::idx_green] = cos_phi_g * r_g + x0_;
            coords.y[channel_order_t::idx_green] = sin_phi_g * r_g + y0_;

            // calculate the 'blue' channel
            coords.x[channel_order_t::idx_blue] -= x0_;
            coords.y[channel_order_t::idx_blue] -= y0_;
            double r_b = std::sqrt(coords.x[channel_order_t::idx_blue] * coords.x[channel_order_t::idx_blue] +
                                   coords.y[channel_order_t::idx_blue] * coords.y[channel_order_t::idx_blue]);
            double cos_phi_b = coords.x[channel_order_t::idx_blue] / r_b;
            double sin_phi_b = coords.y[channel_order_t::idx_blue] / r_b;
            r_b = (((a_ * r_b + b_) * r_b + c_) * r_b + d_) * r_b;

            coords.x[channel_order_t::idx_blue] = cos_phi_b * r_b + x0_;
            coords.y[channel_order_t::idx_blue] = sin_phi_b * r_b + y0_;
        }

        IGeomCorrectionModel* PTLensGeomModel::clone() const
        {
            return new PTLensGeomModel(*this);
        }

    } // namespace phtr::model

} // namespace phtr
