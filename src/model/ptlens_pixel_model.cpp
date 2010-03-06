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

#include <photoropter/model/ptlens_pixel_model.h>

namespace phtr
{

    namespace model
    {

        /* ****************************************
         * PTLensGeomModel
         * **************************************** */

        PTLensPixelModel::
        PTLensPixelModel(double param_aspect, double input_aspect,
                         double param_crop, double input_crop)
                : CorrectionModelBase(param_aspect, input_aspect, param_crop, input_crop)
        {
            for (size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                a_[i] = 0;
                b_[i] = 0;
                c_[i] = 0;
                d_[i] = 1.0;
                x0_[i] = 0;
                y0_[i] = 0;
            }
        }

        PTLensPixelModel::
        PTLensPixelModel(double input_aspect)
                : CorrectionModelBase(input_aspect)
        {
            for (size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                a_[i] = 0;
                b_[i] = 0;
                c_[i] = 0;
                d_[i] = 1.0;
                x0_[i] = 0;
                y0_[i] = 0;
            }
        }

        void
        PTLensPixelModel::
        set_model_params_single(size_t chan_idx, double a, double b, double c, double d)
        {
            a_[chan_idx] = a * std::pow(coord_fact_, 3);
            b_[chan_idx] = b * std::pow(coord_fact_, 2);
            c_[chan_idx] = c * coord_fact_;
            d_[chan_idx] = d;
        }

        void
        PTLensPixelModel::
        set_model_params(double a, double b, double c, double d)
        {
            for (size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                set_model_params_single(i, a, b, c, d);
            }
        }

        void
        PTLensPixelModel::
        set_model_params_single(size_t chan_idx, double a, double b, double c)
        {
            double d = 1.0 - (a + b + c);
            set_model_params_single(chan_idx, a, b, c, d);
        }

        void
        PTLensPixelModel::
        set_model_params(double a, double b, double c)
        {
            for (size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                set_model_params_single(i, a, b, c);
            }
        }

        void
        PTLensPixelModel::
        get_model_params(size_t chan_idx, double& a, double& b, double& c, double& d) const
        {
            a = a_[chan_idx] / std::pow(coord_fact_, 3);
            b = b_[chan_idx] / std::pow(coord_fact_, 2);
            c = c_[chan_idx] / coord_fact_;
            d = d_[chan_idx];
        }

        void
        PTLensPixelModel::
        set_centre_shift_single(size_t chan_idx, interp_coord_t x0, interp_coord_t y0)
        {
            x0_[chan_idx] = x0;
            y0_[chan_idx] = y0;
        }

        void
        PTLensPixelModel::
        set_centre_shift(interp_coord_t x0, interp_coord_t y0)
        {
            for (size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                x0_[i] = x0;
                y0_[i] = y0;
            }
        }

        void
        PTLensPixelModel::
        get_centre_shift(size_t chan_idx, interp_coord_t& x0, interp_coord_t& y0) const
        {
            x0 = x0_[chan_idx];
            y0 = y0_[chan_idx];
        }

        void
        PTLensPixelModel::
        get_src_coords(mem::CoordTupleMono& coords) const
        {
            get_src_coords_impl(coords);
        }

        void
        PTLensPixelModel::
        get_src_coords(mem::CoordTupleRGB& coords) const
        {
            get_src_coords_impl(coords);
        }

        void
        PTLensPixelModel::
        get_src_coords(mem::CoordTupleRGBA& coords) const
        {
            get_src_coords_impl(coords);
        }

        PTLensPixelModel* PTLensPixelModel::clone() const
        {
            return new PTLensPixelModel(*this);
        }

        template <typename coord_tuple_T>
        void
        PTLensPixelModel::
        get_src_coords_impl(coord_tuple_T& coords) const
        {
            typedef typename coord_tuple_T::channel_order_t channel_order_t;
            typedef typename channel_order_t::colour_tuple_t colour_tuple_t;

            for (size_t i = 0; i < colour_tuple_t::num_vals; ++i)
            {
                coords.x[i] -= x0_[i];
                coords.y[i] -= y0_[i];
                double r_r = std::sqrt(coords.x[i] * coords.x[i] +
                                       coords.y[i] * coords.y[i]);
                double cos_phi_r = coords.x[i] / r_r;
                double sin_phi_r = coords.y[i] / r_r;
                r_r = (((a_[i] * r_r + b_[i]) * r_r + c_[i]) * r_r + d_[i]) * r_r;

                coords.x[i] = cos_phi_r * r_r + x0_[i];
                coords.y[i] = sin_phi_r * r_r + y0_[i];
            }

        }

    } // namespace phtr::model

} // namespace phtr
