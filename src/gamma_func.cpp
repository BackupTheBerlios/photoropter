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

#include <photoropter/gamma_func.h>

namespace phtr
{

    namespace gamma
    {

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

        GammaEMOR::GammaEMOR()
        {
            coeff_.clear();
            coeff_.resize(coeff_num_, 0);
        }

        util::SetParam<GammaEMOR::coeff_iter_t> GammaEMOR::set_params(double param1)
        {
            coeff_.clear();
            coeff_.resize(coeff_num_, 0);

            return util::SetParam<coeff_iter_t>(coeff_.begin())(param1);
        }

        template <class iterable_t>
        void GammaEMOR::set_param_list(const iterable_t& params)
        {

            coeff_.clear();
            coeff_.resize(coeff_num_, 0);

            coeff_iter_t coeff_iter;
            typename iterable_t::const_iterator param_iter;

            for (coeff_iter = coeff_.begin(), param_iter = params.begin();
                    coeff_iter != coeff_.end() && param_iter != params.end();
                    ++coeff_iter, ++param_iter)
            {
                *coeff_iter = *param_iter;
            }

        }

        double GammaEMOR::gamma(double value) const
        {

            if (value <= 0.0)
            {
                return 0.0;
            }
            else if (value >= 1.0)
            {
                return 1.0;
            }

            double pos = std::floor(value * (sample_num_ - 1));
            double offset = (value * (sample_num_ - 1)) - pos;
            size_t index = static_cast<size_t>(pos);

            double val = g0_[index] * (1.0 - offset) + g0_[index + 1] * offset;

            double h_val;
            for (size_t i = 0; i < coeff_num_; ++i)
            {
                const float* cur_hinv = hinv_[i];
                h_val = cur_hinv[index] * (1.0 - offset) + cur_hinv[index + 1] * offset;

                val += h_val * coeff_[i];
            }

            return val;

        }

        double GammaEMOR::inv_gamma(double value) const
        {

            if (value <= 0.0)
            {
                return 0.0;
            }
            else if (value >= 1.0)
            {
                return 1.0;
            }

            double pos = std::floor(value * (sample_num_ - 1));
            double offset = (value * (sample_num_ - 1)) - pos;
            size_t index = static_cast<size_t>(pos);

            double val = f0_[index] * (1.0 - offset) + f0_[index + 1] * offset;

            double h_val;
            for (size_t i = 0; i < coeff_num_; ++i)
            {
                const float* cur_h = h_[i];
                h_val = cur_h[index] * (1.0 - offset) + cur_h[index + 1] * offset;

                val += h_val * coeff_[i];
            }

            return val;

        }


        /* Include EMoR curve definitions */
#include "modpar_emor.h"
#include "modpar_invemor.h"
        /// @cond
        const float* GammaEMOR::h_[] =
        {
            GammaEMOR::h01_, GammaEMOR::h02_, GammaEMOR::h03_, GammaEMOR::h04_, GammaEMOR::h05_,
            GammaEMOR::h06_, GammaEMOR::h07_, GammaEMOR::h08_, GammaEMOR::h09_, GammaEMOR::h10_,
            GammaEMOR::h11_, GammaEMOR::h12_, GammaEMOR::h13_, GammaEMOR::h14_, GammaEMOR::h15_,
            GammaEMOR::h16_, GammaEMOR::h17_, GammaEMOR::h18_, GammaEMOR::h19_, GammaEMOR::h20_,
            GammaEMOR::h21_, GammaEMOR::h22_, GammaEMOR::h23_, GammaEMOR::h24_, GammaEMOR::h25_
        };

        const float* GammaEMOR::hinv_[] =
        {
            GammaEMOR::hinv01_, GammaEMOR::hinv02_, GammaEMOR::hinv03_, GammaEMOR::hinv04_, GammaEMOR::hinv05_,
            GammaEMOR::hinv06_, GammaEMOR::hinv07_, GammaEMOR::hinv08_, GammaEMOR::hinv09_, GammaEMOR::hinv10_,
            GammaEMOR::hinv11_, GammaEMOR::hinv12_, GammaEMOR::hinv13_, GammaEMOR::hinv14_, GammaEMOR::hinv15_,
            GammaEMOR::hinv16_, GammaEMOR::hinv17_, GammaEMOR::hinv18_, GammaEMOR::hinv19_, GammaEMOR::hinv20_,
            GammaEMOR::hinv21_, GammaEMOR::hinv22_, GammaEMOR::hinv23_, GammaEMOR::hinv24_, GammaEMOR::hinv25_
        };
        /// @endcond

    } // namespace phtr::gamma

} // namespace phtr
