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

#ifndef PHTR_SUBPIXEL_CORRECTION_MODEL_H__
#define PHTR_SUBPIXEL_CORRECTION_MODEL_H__

#include <photoropter/types.h>
#include <photoropter/mem/coord_tuple.h>

namespace phtr
{

    namespace model
    {

        /**
        * @brief Interface base class for geometrical lens correction models.
        * @details The corrections models are implemented using a 'functionid' pattern.
        */
        class ISubpixelCorrectionModel
        {

            public:
                /**
                 * @ brief (Dummy) Destructor.
                 */
                virtual ~ISubpixelCorrectionModel() {};

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                virtual void get_src_coords(mem::CoordTupleRGB& coords) const = 0;

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                virtual void get_src_coords(mem::CoordTupleRGBA& coords) const = 0;

            public:
                /**
                * @brief Create a clone of the correction %model functionoid.
                * @return The clone.
                */
                virtual ISubpixelCorrectionModel* clone() const = 0;

        }; // class ISubpixelCorrectionModel

    } // namespace phtr::model

} // namespace phtr

#endif // PHTR_SUBPIXEL_CORRECTION_MODEL_H__
