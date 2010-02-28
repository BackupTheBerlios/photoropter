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

#ifndef PHTR_COORD_TUPLE_H__
#define PHTR_COORD_TUPLE_H__

#include <photoropter/mem/colour_tuple.h>
#include <photoropter/types.h>

namespace phtr
{

    namespace mem
    {

        ///@cond PROTECTED

        struct ChannelOrderRGB;
        struct ChannelOrderRGBA;

        /**
         * @brief A tuple containing coordinate pairs.
         */
        template <typename channel_order_T, size_t num_vals_T>
        struct CoordTuple
        {
            /**
             * @brief Channel order information.
             */
            typedef channel_order_T channel_order_t;

            /**
             * @brief Constructor.
             */
            CoordTuple()
            {
                //NIL
            }

            /**
             * Copy constructor.
             * @param[in] orig The original object.
             */
            inline CoordTuple(const CoordTuple& orig);

            /**
             * Assignment.
             * @param[in] orig The original object.
             * @return Reference to the current object.
             */
            inline CoordTuple& operator=(const CoordTuple& orig);

            /**
             * @brief The x values.
             */
            interp_coord_t x[num_vals_T];

            /**
             * @brief The y values.
             */
            interp_coord_t y[num_vals_T];

        };

        /**
         * @brief A tuple containing 3 coordinate pairs.
         */
        typedef CoordTuple<ChannelOrderRGB, 3> CoordTupleRGB;

        /**
         * @brief A tuple containing 4 coordinate pairs.
         */
        typedef CoordTuple<ChannelOrderRGBA, 4> CoordTupleRGBA;

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr

#include <photoropter/mem/coord_tuple.tpl.h>

#endif // PHTR_COORD_TUPLE_H__
