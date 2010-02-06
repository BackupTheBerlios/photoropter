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

#ifndef __LENS_CORRECTION_MODEL_H__
#define __LENS_CORRECTION_MODEL_H__

#include "types.h"

namespace phtr
{

    /**
    * \brief Interface base class for lens correction models.
    * \details The corrections models are implemented using a 'functionid' pattern.
    */
    class ILensCorrectionModel
    {

        public:
            /**
            * \brief Get the corrected source image coordinates for the current position.
            * \param[in,out] x_r The corresponding x coordinate for the 'red' channel
            *                     in the source image.
            * \param[in,out] y_r The corresponding y coordinate for the 'red' channel
            *                     in the source image.
            * \param[in,out] x_g The corresponding x coordinate for the 'green' channel
            *                     in the source image.
            * \param[in.out] y_g The corresponding y coordinate for the 'green' channel
            *                     in the source image.
            * \param[in.out] x_b The corresponding x coordinate for the 'blue' channel
            *                     in the source image.
            * \param[in,out] y_b The corresponding y coordinate for the 'blue' channel
            *                     in the source image.
            */
            virtual void get_src_coords(interp_coord_t& x_r, interp_coord_t& y_r,
                                        interp_coord_t& x_g, interp_coord_t& y_g,
                                        interp_coord_t& x_b, interp_coord_t& y_b) = 0;

    };

    /**
    * \brief The PTLens geometric correction model.
    * \details The PTLens correction model implements the following formular: \[
    * r_{src} = (a r_{dst}^3 + b r_{dst}^2 + c r_{dst} + d)  r_{dst}
    * \]
    * Usually, 'd' is left at a fixed value of 1. Additionally, coordinates
    * describing a shift of the center are often used. Hugin and PanoTools often
    * call these 'd' and 'e', thus creating a bit of a confusion concerning the 'd'
    * parameter in the formula above. Because of that, we will use the format
    * (x0,y0) to designate the center shift.
    */
    class PTLensGeomModel : public ILensCorrectionModel
    {

        public:
            /**
            * \brief Constructor.
            * \param[in] a The 'a' parameter.
            * \param[in] b The 'b' parameter.
            * \param[in] c The 'c' parameter.
            * \param[in] d The 'd' parameter.
            * \param[in] x0 The 'x0' parameter.
            * \param[in] y0 The 'y0' parameter.
            */
            PTLensGeomModel(double a, double b, double c, double d = 1.0, double x0 = 0.0, double y0 = 0.0);

        public:
            /**
            * \brief Get the corrected source image coordinates for the current position.
            * \param[in,out] x_r The corresponding x coordinate for the 'red' channel
            *                     in the source image.
            * \param[in,out] y_r The corresponding y coordinate for the 'red' channel
            *                     in the source image.
            * \param[in,out] x_g The corresponding x coordinate for the 'green' channel
            *                     in the source image.
            * \param[in.out] y_g The corresponding y coordinate for the 'green' channel
            *                     in the source image.
            * \param[in.out] x_b The corresponding x coordinate for the 'blue' channel
            *                     in the source image.
            * \param[in,out] y_b The corresponding y coordinate for the 'blue' channel
            *                     in the source image.
            */
            virtual void get_src_coords(interp_coord_t& x_r, interp_coord_t& y_r,
                                        interp_coord_t& x_g, interp_coord_t& y_g,
                                        interp_coord_t& x_b, interp_coord_t& y_b);

        private:
            double a_;
            double b_;
            double c_;
            double d_;
            double x0_;
            double y0_;

    };

} // namespace phtr

#endif // __LENS_CORRECTION_MODEL_H__
