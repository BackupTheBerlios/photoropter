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

#include <photoropter/model/scaler_geom_model.h>

namespace phtr
{

    namespace model
    {

        /* ****************************************
        * ScalerGeomModel
        * **************************************** */

        ScalerGeomModel::
        ScalerGeomModel(double param_aspect, double input_aspect,
                        double param_crop, double input_crop)
            : CorrectionModelBase(param_aspect, input_aspect, param_crop, input_crop)
        {
            for(size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                k_[i] = 1.0;
                x0_[i] = 0;
                y0_[i] = 0;
            }
        }

        ScalerGeomModel::
        ScalerGeomModel(double input_aspect)
            : CorrectionModelBase(input_aspect)
        {
            for(size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                k_[i] = 1.0;
                x0_[i] = 0;
                y0_[i] = 0;
            }
        }

        void
        ScalerGeomModel::
        set_model_param_single(size_t chan_idx, double k)
        {
            k_[chan_idx] = k;
        }

        void
        ScalerGeomModel::
        set_model_param(double k)
        {
            for(size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                set_model_param_single(i, k);
            }
        }

        void
        ScalerGeomModel::
        get_model_param(size_t chan_idx, double& k) const
        {
            k = k_[chan_idx];
        }

        void
        ScalerGeomModel::
        set_centre_shift_single(size_t chan_idx, interp_coord_t x0, interp_coord_t y0)
        {
            x0_[chan_idx] = x0;
            y0_[chan_idx] = y0;
        }

        void
        ScalerGeomModel::
        set_centre_shift(interp_coord_t x0, interp_coord_t y0)
        {
            for(size_t i = 0; i < mem::PHTR_MAX_CHANNELS; ++i)
            {
                x0_[i] = x0;
                y0_[i] = y0;
            }
        }

        void
        ScalerGeomModel::
        get_centre_shift(size_t chan_idx, interp_coord_t& x0, interp_coord_t& y0) const
        {
            x0 = x0_[chan_idx];
            y0 = y0_[chan_idx];
        }

        void
        ScalerGeomModel::
        get_src_coords(mem::CoordTupleRGB& coords) const
        {
            get_src_coords_impl(coords);
        }

        void
        ScalerGeomModel::
        get_src_coords(mem::CoordTupleRGBA& coords) const
        {
            get_src_coords_impl(coords);
        }

        IGeomCorrectionModel* ScalerGeomModel::clone() const
        {
            return new ScalerGeomModel(*this);
        }

        template <typename coord_tuple_T>
        void
        ScalerGeomModel::
        get_src_coords_impl(coord_tuple_T& coords) const
        {
            typedef typename coord_tuple_T::channel_order_t channel_order_t;
            typedef typename channel_order_t::colour_tuple_t colour_tuple_t;

            for(size_t i = 0; i < colour_tuple_t::num_vals; ++i)
            {
                coords.x[i] -= x0_[i];
                coords.y[i] -= y0_[i];

                coords.x[i] /= k_[i];
                coords.y[i] /= k_[i];

                coords.x[i] += x0_[i];
                coords.y[i] += y0_[i];
            }

        }

    } // namespace phtr::model

} // namespace phtr
