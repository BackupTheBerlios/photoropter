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

#include <photoropter/mem_layout.h>
#include <photoropter/colour_correction_model.h>

namespace phtr
{

    namespace model
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
        set_model_params(double a, double b, double c)
        {
            a_ = a * std::pow(coord_fact_, 6);
            b_ = b * std::pow(coord_fact_, 4);
            c_ = c * std::pow(coord_fact_, 2);
        }

        void VignettingColourModel::
        get_model_params(double& a, double& b, double& c) const
        {
            a = a_ / std::pow(coord_fact_, 6);
            b = b_ / std::pow(coord_fact_, 4);
            c = c_ / std::pow(coord_fact_, 2);
        }

        void
        VignettingColourModel::
        set_centre_shift(interp_coord_t x0, interp_coord_t y0)
        {
            x0_ = x0;
            y0_ = y0;
        }

        void
        VignettingColourModel::
        get_centre_shift(interp_coord_t& x0, interp_coord_t& y0) const
        {
            x0 = x0_;
            y0 = y0_;
        }


        void
        VignettingColourModel::
        get_correction_factors(const mem::CoordTupleRGB& coords,
                               mem::ColourTupleRGB& factors) const
        {
            get_correction_factors_impl(coords, factors);
        }

        void
        VignettingColourModel::
        get_correction_factors(const mem::CoordTupleRGBA& coords,
                               mem::ColourTupleRGBA& factors) const
        {
            typedef mem::CoordTupleRGBA::channel_order_t channel_order_t;

            get_correction_factors_impl(coords, factors);

            factors.value[channel_order_t::idx_alpha] = 1.0;
        }

        template <typename coord_tuple_T>
        void
        VignettingColourModel::
        get_correction_factors_impl(const coord_tuple_T& coords,
                                    typename coord_tuple_T::channel_order_t::colour_tuple_t& factors) const
        {

            typedef typename coord_tuple_T::channel_order_t channel_order_t;
            typedef typename channel_order_t::colour_tuple_t colour_tuple_t;

            double x_r = coords.x[channel_order_t::idx_red] - x0_;
            double y_r = coords.y[channel_order_t::idx_red] - y0_;
            double r2_r = x_r * x_r + y_r * y_r;

            factors.value[channel_order_t::idx_red] = 1.0 / (((a_ * r2_r + b_) * r2_r + c_) * r2_r + 1.0);

            double x_g = coords.x[channel_order_t::idx_green] - x0_;
            double y_g = coords.y[channel_order_t::idx_green] - y0_;
            double r2_g = x_g * x_g + y_g * y_g;

            factors.value[channel_order_t::idx_green] = 1.0 / (((a_ * r2_g + b_) * r2_g + c_) * r2_g + 1.0);

            double x_b = coords.x[channel_order_t::idx_blue] - x0_;
            double y_b = coords.y[channel_order_t::idx_blue] - y0_;
            double r2_b = x_b * x_b + y_b * y_b;

            factors.value[channel_order_t::idx_blue] = 1.0 / (((a_ * r2_b + b_) * r2_b + c_) * r2_b + 1.0);

        }

        IColourCorrectionModel* VignettingColourModel::clone() const
        {
            return new VignettingColourModel(*this);
        }

        HuginVignettingModel::
        HuginVignettingModel(double param_aspect, double input_aspect,
                             double param_crop, double input_crop)
                : VignettingColourModel(param_aspect, input_aspect, param_crop, input_crop)
        {
            //NIL
        }

        HuginVignettingModel::
        HuginVignettingModel(double input_aspect)
                : VignettingColourModel(input_aspect)
        {
            //NIL
        }

        void HuginVignettingModel::
        set_model_params(double a, double b, double c)
        {
            double hugin_fact = 1.0 / std::sqrt(1.0 + param_aspect_ * param_aspect_);
            a_ = a * std::pow(coord_fact_ * hugin_fact, 6);
            b_ = b * std::pow(coord_fact_ * hugin_fact, 4);
            c_ = c * std::pow(coord_fact_ * hugin_fact, 2);
        }

        void HuginVignettingModel::
        get_model_params(double& a, double& b, double& c) const
        {
            double hugin_fact = 1.0 / std::sqrt(1.0 + param_aspect_ * param_aspect_);
            a = a_ /  std::pow(coord_fact_ * hugin_fact, 6);
            b = b_ / std::pow(coord_fact_ * hugin_fact, 4);
            c = c_ / std::pow(coord_fact_ * hugin_fact, 2);
        }

        IColourCorrectionModel* HuginVignettingModel::clone() const
        {
            return new HuginVignettingModel(*this);
        }

    } // namespace phtr::model

} // namespace phtr
