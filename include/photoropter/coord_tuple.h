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

#ifndef __PHTR_COORD_TUPLE_H__
#define __PHTR_COORD_TUPLE_H__

#include <photoropter/colour_tuple.h>
#include <photoropter/types.h>

namespace phtr
{

    namespace mem
    {

        ///@cond PROTECTED

        struct ChannelOrderRGB;

        /**
         * @brief A tuple containing 3 coordinate pairs.
         */
        struct CoordTupleRGB
        {
            /**
             * @brief The corresponding colour tuple type.
             */
            typedef ColourTupleRGB colour_tuple_t;

            /**
             * @brief Channel order information.
             */
            typedef ChannelOrderRGB channel_order_t;

            /**
             * @brief Constructor.
             */
            CoordTupleRGB()
            {
                //NIL
            }

            /**
             * Copy constructor.
             * @param[in] orig The original object.
             */
            inline CoordTupleRGB(const CoordTupleRGB& orig);

            /**
             * Assignment.
             * @param[in] orig The original object.
             * @return Reference to the current object.
             */
            inline CoordTupleRGB& operator=(const CoordTupleRGB& orig);

            /**
             * @brief The x values.
             */
            interp_coord_t x[3];

            /**
             * @brief The y values.
             */
            interp_coord_t y[3];

        };

        struct ColourTupleRGBA;

        /**
         * @brief A tuple containing 3 coordinate pairs.
         */
        struct CoordTupleRGBA
        {

            /**
             * @brief The corresponding colour tuple type.
             */
            typedef ColourTupleRGBA colour_tuple_t;

            /**
                * @brief Constructor.
                * @note All members are set to 0.
                */
            CoordTupleRGBA()
                    : x_r(0),
                    y_r(0),
                    x_g(0),
                    y_g(0),
                    x_b(0),
                    y_b(0),
                    x_a(0),
                    y_a(0)
            {
                //NIL
            }

            /**
             * @brief The x coordinate for the 'red' channel.
             */
            interp_coord_t x_r;

            /**
             * @brief The y coordinate for the 'red' channel.
             */
            interp_coord_t y_r;

            /**
             * @brief The x coordinate for the 'green' channel.
             */
            interp_coord_t x_g;

            /**
             * @brief The y coordinate for the 'green' channel.
             */
            interp_coord_t y_g;

            /**
             * @brief The x coordinate for the 'blue' channel.
             */
            interp_coord_t x_b;

            /**
             * @brief The y coordinate for the 'blue' channel.
             */
            interp_coord_t y_b;

            /**
             * @brief The x coordinate for the 'alpha' channel.
             */
            interp_coord_t x_a;

            /**
             * @brief The y coordinate for the 'alpha' channel.
             */
            interp_coord_t y_a;

        };

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr

#include <photoropter/coord_tuple.inl.h>

#endif // __PHTR_COORD_TUPLE_H__
