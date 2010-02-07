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

#include "Photoropter/geom_correction_model.h"

namespace phtr
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
    set_model_params(double a, double b, double c, double d,
                     interp_coord_t x0, interp_coord_t y0)
    {
        a_ = a * std::pow(coord_fact_, 3);
        b_ = b * std::pow(coord_fact_, 2);
        c_ = c * coord_fact_;
        d_ = d;
        x0_ = x0;
        y0_ = y0;
    }

    void
    PTLensGeomModel::
    get_src_coords(interp_coord_t& x_r, interp_coord_t& y_r,
                   interp_coord_t& x_g, interp_coord_t& y_g,
                   interp_coord_t& x_b, interp_coord_t& y_b) const
    {
        // calculate the 'red' channel
        x_r -= x0_;
        y_r -= y0_;
        double r_r = std::sqrt(x_r * x_r + y_r * y_r);
        double cos_phi_r = x_r / r_r;
        double sin_phi_r = y_r / r_r;
        r_r = (((a_ * r_r + b_) * r_r + c_) * r_r + d_) * r_r;

        x_r = cos_phi_r * r_r + x0_;
        y_r = sin_phi_r * r_r + y0_;

        // calculate the 'green' channel
        x_g -= x0_;
        y_g -= y0_;
        double r_g = std::sqrt(x_g * x_g + y_g * y_g);
        double cos_phi_g = x_g / r_g;
        double sin_phi_g = y_g / r_g;
        r_g = (((a_ * r_g + b_) * r_g + c_) * r_g + d_) * r_g;

        x_g = cos_phi_g * r_g + x0_;
        y_g = sin_phi_g * r_g + y0_;

        // calculate the 'blue' channel
        x_b -= x0_;
        y_b -= y0_;
        double r_b = std::sqrt(x_b * x_b + y_b * y_b);
        double cos_phi_b = x_b / r_b;
        double sin_phi_b = y_b / r_b;
        r_b = (((a_ * r_b + b_) * r_b + c_) * r_b + d_) * r_b;

        x_b = cos_phi_b * r_b + x0_;
        y_b = sin_phi_b * r_b + y0_;
    }

    IGeomCorrectionModel* PTLensGeomModel::clone()
    {
        return new PTLensGeomModel(*this);
    }

} // namespace phtr
