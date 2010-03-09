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

namespace phtr
{
    namespace geom
    {

        FisheyeOrtho::
        FisheyeOrtho()
                : focal_length_(10.0)
        {
            //NIL
        }

        void
        FisheyeOrtho::
        set_focal_length(double focal_length)
        {
            focal_length_ = focal_length;
        }

        bool
            FisheyeOrtho::
            to_spherical_coords(const double& x,
            const double& y,
            double& phi,
            double& theta) const
        {
            double r = std::sqrt(x * x + y * y);

            phi = std::acos(x / r);
            if (y > 0)
            {
                phi = 2 * PHTR_PI - phi;
            }

            double asin_arg = r / focal_length_;
            if (asin_arg >= 1.0)
            {
                return false;
            }

            theta = std::asin(asin_arg);

            return true;
        }

        bool
            FisheyeOrtho::
            to_cartesian_coords(const double& phi,
            const double& theta,
            double& x,
            double& y) const
        {
            if (theta >= PHTR_PI / 2)
            {
                return false;
            }

            double r = std::sin(theta) * focal_length_;

            x = std::cos(phi) * r;
            y = -std::sin(phi) * r;

            return true;
        }

    } // namespace phtr::geometry

} // namespace phtr
