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

#ifndef PHTR_RECTILINEAR_H__
#define PHTR_RECTILINEAR_H__

#include <cmath>

namespace phtr
{
    namespace geom
    {

        /**
         * @brief Rectilinear ('gnomonic') lens geometry.
         */
        class Rectilinear
        {

            public:
                /**
                * @brief Constructor.
                */
                inline Rectilinear();

            public:
                /**
                * @brief Set the focal length.
                * @param focal_length The lens's focal length.
                */
                inline void set_focal_length(double focal_length);

            public:
                /**
                * @brief Convert to spherical coordinates.
                * @param[in]  x     The (cartesian) x coordinate.
                * @param[in]  y     The (cartesian) y coordinate.
                * @param[out] phi   The angle in the image plane.
                * @param[out] theta The angle to the optical axis.
                * @return 'false' if the conversion was not possible, 'true' otherwise.
                */
                inline bool to_spherical_coords(const double& x,
                                                const double& y,
                                                double& phi,
                                                double& theta) const;

            public:
                /**
                * @brief Convert to cartesian coordinates.
                * @param[in]  phi   The angle in the image plane.
                * @param[in]  theta The angle to the optical axis.
                * @param[out] x     The (cartesian) x coordinate.
                * @param[out] y     The (cartesian) y coordinate.
                * @return 'false' if the conversion was not possible, 'true' otherwise.
                */
                inline bool to_cartesian_coords(const double& phi,
                                                const double& theta,
                                                double& x,
                                                double& y) const;

            private:
                /**
                * @brief The lens's focal length.
                */
                double focal_length_;

        }; // class Rectilinear

    } // namespace phtr::geometry

} // namespace phtr

#include <photoropter/geometry/rectilinear.inl.h>

#endif // PHTR_RECTILINEAR_H__
