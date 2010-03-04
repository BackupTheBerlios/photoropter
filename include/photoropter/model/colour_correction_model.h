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

#ifndef PHTR_COLOUR_CORRECTION_MODEL_H__
#define PHTR_COLOUR_CORRECTION_MODEL_H__

#include <photoropter/mem/coord_tuple.h>
#include <photoropter/mem/colour_tuple.h>
#include <photoropter/model/correction_model_base.h>

namespace phtr
{

    namespace model
    {

        /**
        * @brief Interface base class for colour correction models.
        * @details The corrections models are implemented using a 'functionid' pattern.
        */
        class IColourCorrectionModel
        {

            public:
                /**
                 * @ brief (Dummy) Destructor.
                 */
                virtual ~IColourCorrectionModel() {};

            public:
                /**
                * @brief Get the correction factors for a given position.
                * @param[in] coords The coordinates in the source image.
                * @param[out] factors The correction factors.
                */
                virtual void get_correction_factors(const mem::CoordTupleRGB& coords,
                                                    mem::ColourTupleRGB& factors) const = 0;

            public:
                /**
                * @brief Get the correction factors for a given position.
                * @param[in] coords The coordinates in the source image.
                * @param[out] factors The correction factors.
                */
                virtual void get_correction_factors(const mem::CoordTupleRGBA& coords,
                                                    mem::ColourTupleRGBA& factors) const = 0;

            public:
                /**
                * @brief Create a clone of the correction model functionoid.
                * @return The clone.
                */
                virtual IColourCorrectionModel* clone() const = 0;

        }; // class IColourCorrectionModel

    } // namespace phtr::model

} // namespace phtr

#endif // PHTR_COLOUR_CORRECTION_MODEL_H__
