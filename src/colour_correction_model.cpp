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

#include <photoropter/colour_correction_model.h>

namespace phtr
{

    VignettingColourModel::
    VignettingColourModel(double param_aspect, double input_aspect,
                          double param_crop, double input_crop)
            : CorrectionModelBase(param_aspect, input_aspect, param_crop, input_crop),
            a_(0),
            b_(0),
            c_(0),
            x0_(0),
            y0_(0)
    {
        //NIL
    }

    VignettingColourModel::
    VignettingColourModel(double input_aspect)
            : CorrectionModelBase(input_aspect),
            a_(0),
            b_(0),
            c_(0),
            x0_(0),
            y0_(0)
    {
        //NIL
    }

    void VignettingColourModel::
    set_model_params(double a, double b, double c,
                     interp_coord_t x0, interp_coord_t y0)
    {
        a_ = a * std::pow(coord_fact_, 6);
        b_ = b * std::pow(coord_fact_, 4);
        c_ = c * std::pow(coord_fact_, 2);
        x0_ = x0;
        y0_ = y0;
    }

    inline void VignettingColourModel::
    get_correction_factors(interp_coord_t src_x_r, interp_coord_t src_y_r,
                           interp_coord_t src_x_g, interp_coord_t src_y_g,
                           interp_coord_t src_x_b, interp_coord_t src_y_b,
                           double& fact_r, double& fact_g, double& fact_b) const
    {
        src_x_r -= x0_;
        src_y_r -= y0_;
        double r_r = std::sqrt(src_x_r * src_x_r + src_y_r * src_y_r);

        fact_r = 1.0 / (((a_ * r_r * r_r + b_) * r_r * r_r + c_) * r_r * r_r + 1.0);

        src_x_g -= x0_;
        src_y_g -= y0_;
        double r_g = std::sqrt(src_x_g * src_x_g + src_y_g * src_y_g);

        fact_g = 1.0 / (((a_ * r_g * r_g + b_) * r_g * r_g + c_) * r_g * r_g + 1.0);

        src_x_b -= x0_;
        src_y_b -= y0_;
        double r_b = std::sqrt(src_x_b * src_x_b + src_y_b * src_y_b);

        fact_b = 1.0 / (((a_ * r_b * r_b + b_) * r_b * r_b + c_) * r_b * r_b + 1.0);

    }

    IColourCorrectionModel* VignettingColourModel::clone() const
    {
        return new VignettingColourModel(*this);
    }

} // namespace phtr
