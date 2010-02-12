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

        /* Include EMoR curve definitions */
#include "modpar_emor.h"
#include "modpar_invemor.h"

    } // namespace phtr::gamma

} // namespace phtr
