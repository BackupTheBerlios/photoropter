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

#ifndef PHTR_TYPES_H__
#define PHTR_TYPES_H__

#include <cstddef>

namespace phtr
{

    /**
    * @brief Channel value type.
    */
    typedef double interp_channel_t;

    /**
    * @brief Coordinate type.
    */
    typedef size_t coord_t;

    /**
    * @brief Type used for the image transformation 'lines' loop.
    * @details This type needs to be signed for OpenMP 2.0, so it
    * is defined as 'long' when only OpenMP 2.0 is available
    * (i.e., Visual Studio).
    */
#if (defined HAVE_OPENMP) && (!defined OPENMP3)
    typedef long omp_coord_t;
#else
    typedef size_t omp_coord_t;
#endif

    /**
    * @brief Type for interpolated coordinates.
    */
    typedef double interp_coord_t;

    /**
    * @brief The mathematical constant 'pi'.
    */
    static const double PHTR_PI = 3.14159265358979323846;


} // namespace phtr

#endif // PHTR_TYPES_H__
