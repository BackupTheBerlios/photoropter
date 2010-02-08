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

#include <Photoropter/correction_model_base.h>

namespace phtr
{

    CorrectionModelBase::
    CorrectionModelBase(double param_aspect, double input_aspect,
                        double param_crop, double input_crop)
            : param_aspect_(param_aspect),
            input_aspect_(input_aspect),
            param_crop_(param_crop),
            input_crop_(input_crop),
            coord_fact_(1.0)
    {
        calc_coord_fact();
    }

    CorrectionModelBase::
    CorrectionModelBase(double input_aspect)
            : input_aspect_(input_aspect),
            param_crop_(1.0),
            input_crop_(1.0),
            coord_fact_(1.0)
    {
        param_aspect_ = (input_aspect_ > 1) ? input_aspect_ : (1.0 / input_aspect_);

        calc_coord_fact();
    }

    void
    CorrectionModelBase::
    set_coord_params(double param_aspect, double input_aspect,
                     double param_crop, double input_crop)
    {
        param_aspect_ = param_aspect;
        input_aspect_ = input_aspect;
        param_crop_ = param_crop;
        input_crop_ = input_crop;

        calc_coord_fact();
    }

    void
    CorrectionModelBase::
    calc_coord_fact()
    {
        /* see technical documentation for information on correct dealing with
        aspect ratio and crop factor */
        coord_fact_ = std::sqrt(1 + param_aspect_ * param_aspect_) /
                      std::sqrt(1 + input_aspect_ * input_aspect_) *
                      param_crop_ / input_crop_;
    }

} // namespace phtr
