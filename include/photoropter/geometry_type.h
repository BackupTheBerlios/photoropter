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

#ifndef PHTR_GEOMETRY_TYPE_H__
#define PHTR_GEOMETRY_TYPE_H__

namespace phtr
{

    /**
     * @brief Struct listing different lens geometries.
     */
    struct Geometry
    {

        /**
         * @brief Enum containing the actual geometry entries.
         */
        enum type
        {
            /**
             * @brief Rectilinear geometry.
             */
            rectilinear,

            /**
             * @brief 'Equidistant' fisheye geometry.
             */
            fisheye_equidistant,

            /**
             * @brief 'Equisolid' fisheye geometry.
             */
            fisheye_equisolid,

            /**
             * @brief 'Stereographic' fisheye geometry.
             */
            fisheye_stereo
        };
    };

} // namespace phtr

#endif // PHTR_GEOMETRY_TYPE_H__
