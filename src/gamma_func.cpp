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
#include <algorithm>

#include <photoropter/gamma_func.h>

namespace phtr
{

    namespace gamma
    {

        ///@cond PROTECTED

        GammaGeneric::GammaGeneric(double gam)
            : gamma_(gam)
        {
            //NIL
        }

        double GammaGeneric::gamma(double value) const
        {
            return std::pow(value, gamma_);
        }

        double GammaGeneric::inv_gamma(double value) const
        {
            return std::pow(value, 1.0 / gamma_);
        }

        double GammaSRGB::gamma(double value) const
        {
            return (value <= 0.04045) ? value / 12.92 : std::pow((value + 0.055) / 1.055, 2.4);
        }

        double GammaSRGB::inv_gamma(double value) const
        {
            return (value <= 0.0031309) ? 12.92 * value : 1.055 * std::pow(value, 1.0 / 2.4) - 0.055;
        }

        GammaEMORBase::GammaEMORBase()
            : precalc_done_(false)
        {
            coeff_.clear();
            coeff_.resize(coeff_num_, 0);
        }

        util::SetParam<GammaEMORBase::coeff_iter_t>
        GammaEMORBase::
        set_params()
        {
            coeff_.clear();
            coeff_.resize(coeff_num_, 0);
            precalc_done_ = false;

            return util::SetParam<coeff_iter_t>(coeff_.begin());
        }

        template <class iterable_t>
        void
        GammaEMORBase::
        set_param_list(const iterable_t& params)
        {

            coeff_.clear();
            coeff_.resize(coeff_num_, 0);
            precalc_done_ = false;

            coeff_iter_t coeff_iter;
            typename iterable_t::const_iterator param_iter;

            for(coeff_iter = coeff_.begin(), param_iter = params.begin();
                    coeff_iter != coeff_.end() && param_iter != params.end();
                    ++coeff_iter, ++param_iter)
            {
                *coeff_iter = *param_iter;
            }

        }

        double GammaEMORBase::get_function_value(double inp_val, const value_vect_t& xval, const value_vect_t& yval) const
        {

            if(inp_val <= 0.0)
            {
                return 0.0;
            }
            else if(inp_val >= 1.0)
            {
                return 1.0;
            }

            // make sure function values are initialised
            precalc_func();

            // determine index
            size_t index = static_cast<size_t>(std::lower_bound(xval.begin(), xval.end(), inp_val)
                                               - xval.begin());

            // linar interpolation
            /* note: since we checked that the input value is > 1.0, and the first element in
             xval_ is guaranteed to be 0.0, lower_bound will yield a value >= 1 (and < sample_num_,
             since input value is checked that it is < 1.0 as well). */
            double x1 = xval[index - 1];
            double x2 = xval[index];
            double offs1 = inp_val - x1;
            double offs2 = x2 - inp_val;

            double val = (yval[index - 1] * offs2 + yval[index] * offs1) / (x2 - x1);

            return val;

        }

        /* Include EMoR curve definitions */
#include "modpar_emor.h"
#include "modpar_invemor.h"
        /// @cond
        const float* GammaEMORBase::h_[] =
        {
            GammaEMORBase::h01_, GammaEMORBase::h02_, GammaEMORBase::h03_, GammaEMORBase::h04_, GammaEMORBase::h05_,
            GammaEMORBase::h06_, GammaEMORBase::h07_, GammaEMORBase::h08_, GammaEMORBase::h09_, GammaEMORBase::h10_,
            GammaEMORBase::h11_, GammaEMORBase::h12_, GammaEMORBase::h13_, GammaEMORBase::h14_, GammaEMORBase::h15_,
            GammaEMORBase::h16_, GammaEMORBase::h17_, GammaEMORBase::h18_, GammaEMORBase::h19_, GammaEMORBase::h20_,
            GammaEMORBase::h21_, GammaEMORBase::h22_, GammaEMORBase::h23_, GammaEMORBase::h24_, GammaEMORBase::h25_
        };

        const float* GammaEMORBase::hinv_[] =
        {
            GammaEMORBase::hinv01_, GammaEMORBase::hinv02_, GammaEMORBase::hinv03_, GammaEMORBase::hinv04_, GammaEMORBase::hinv05_,
            GammaEMORBase::hinv06_, GammaEMORBase::hinv07_, GammaEMORBase::hinv08_, GammaEMORBase::hinv09_, GammaEMORBase::hinv10_,
            GammaEMORBase::hinv11_, GammaEMORBase::hinv12_, GammaEMORBase::hinv13_, GammaEMORBase::hinv14_, GammaEMORBase::hinv15_,
            GammaEMORBase::hinv16_, GammaEMORBase::hinv17_, GammaEMORBase::hinv18_, GammaEMORBase::hinv19_, GammaEMORBase::hinv20_,
            GammaEMORBase::hinv21_, GammaEMORBase::hinv22_, GammaEMORBase::hinv23_, GammaEMORBase::hinv24_, GammaEMORBase::hinv25_
        };
        /// @endcond

        void GammaEMOR::precalc_func() const
        {
            if(precalc_done_)
            {
                return;
            }

            // reset cache containers
            xval_.clear();
            xval_.resize(sample_num_, 0);
            yval_.clear();
            yval_.resize(sample_num_, 0);

            double ytmp;
            for(size_t i = 0; i < sample_num_; ++i)
            {
                xval_[i] = E_[i];

                ytmp = f0_[i];
                for(size_t j = 0; j < coeff_num_; ++j)
                {
                    ytmp += coeff_[j] * h_[j][i];
                }
                yval_[i] = ytmp;
            }

            precalc_done_ = true;
            return;
        }

        double GammaEMOR::gamma(double value) const
        {
            return get_function_value(value, yval_, xval_);
        }

        double GammaEMOR::inv_gamma(double value) const
        {
            return get_function_value(value, xval_, yval_);
        }

        void GammaInvEMOR::precalc_func() const
        {
            if(precalc_done_)
            {
                return;
            }

            // reset cache containers
            xval_.clear();
            xval_.resize(sample_num_, 0);
            yval_.clear();
            yval_.resize(sample_num_, 0);

            double ytmp;
            double lasty(0.0);
            for(size_t i = 0; i < sample_num_; ++i)
            {
                xval_[i] = B_[i];

                ytmp = g0_[i];
                for(size_t j = 0; j < coeff_num_; ++j)
                {
                    ytmp += coeff_[j] * hinv_[j][i];
                }

                // enforce monotonicity
                if(ytmp < lasty)
                {
                    ytmp = lasty;
                }

                lasty = ytmp;
                yval_[i] = ytmp;
            }

            precalc_done_ = true;
            return;
        }

        double GammaInvEMOR::gamma(double value) const
        {
            return get_function_value(value, xval_, yval_);
        }

        double GammaInvEMOR::inv_gamma(double value) const
        {
            return get_function_value(value, yval_, xval_);
        }

        ///@endcond

    } // namespace phtr::gamma

} // namespace phtr
