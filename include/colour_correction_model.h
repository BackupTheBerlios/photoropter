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

#ifndef __COLOUR_CORRECTION_MODEL_H__
#define __COLOUR_CORRECTION_MODEL_H__

#include "types.h"
#include "channel_type.h"

namespace phtr
{

    /**
    * \brief Interface base class for geometrical lens correction models.
    * \details The corrections models are implemented using a 'functionid' pattern.
    */
    class IColourCorrectionModel
    {

        public:
            /**
            * \brief Get the correction factor for the given position and channel.
            * \oaram[in] chan  The channel (e.g., Channel::red).
            * \param[in] src_x The corresponding x coordinate for the 'red' channel
            *                  in the source image.
            * \param[in] src_y The corresponding y coordinate for the 'red' channel
            *                  in the source image.
            * \return The correction factor.
            */
            virtual double get_correction_factor(Channel::type chan,
                                                 interp_coord_t src_x, interp_coord_t src_y) const = 0;

        public:
            /**
            * \brief Create a clone of the correction model functionoid.
            * \return The clone.
            */
            virtual IColourCorrectionModel* clone() = 0;

    }; // class IColourCorrectionModel

} // namespace phtr

#endif // __COLOUR_CORRECTION_MODEL_H__
