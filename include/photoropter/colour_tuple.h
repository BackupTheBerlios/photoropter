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

#ifndef __PHTR__COLOUR_TUPLE_H__
#define __PHTR__COLOUR_TUPLE_H__

#include <photoropter/types.h>
#include <photoropter/channel_type.h>

namespace phtr
{

    namespace mem
    {

        ///@cond PROTECTED

        /* ****************************************
         * RGB
         * **************************************** */

        struct CoordTupleRGB;
        struct ChannelOrderRGB;

        /**
         * @brief A 3-tuple of RGB channel/colour values.
         */
        struct ColourTupleRGB
        {
            /**
             * @brief The corresponding coordinates tuple type.
             */
            typedef CoordTupleRGB coord_tuple_t;

            /**
             * @brief Channel order information.
             */
            typedef ChannelOrderRGB channel_order_t;

            /**
             * @brief Constructor.
             */
            ColourTupleRGB()
            {
                //NIL
            }

            /**
             * @brief Copy constructor.
             * @param[in] orig The original object.
             */
            inline ColourTupleRGB(const ColourTupleRGB& orig);

            /**
             * @brief Assignment
             * @param[in] orig The original object.
             * @return Reference to the current object.
             */
            inline ColourTupleRGB& operator=(const ColourTupleRGB& orig);

            /**
             * @brief Clear the values.
             */
            inline void clear();

            /**
             * @brief Multiplication with values from another tuple.
             * @note The multiplication is done element-wise.
             * @param[in] other The other tuple.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTupleRGB& operator*=(const ColourTupleRGB& other);

            /**
             * @brief Multiplication with a constant.
             * @param[in] factor The multiplication factor.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTupleRGB& operator*=(interp_channel_t factor);

            /**
             * @brief Addition of values from another tuple.
             * @param[in] other The other tuple.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTupleRGB& operator+=(const ColourTupleRGB& other);

            /**
             * The array of values;
             */
            interp_channel_t value[3];

            /**
             * The number of values (i.e., 3).
             */
            static const size_t num_vals;

            /**
             * The channel types.
             */
            static const Channel::type channel_type[];

        }; // struct ColourTupleRGB

        /**
         * @brief Multiplication with a constant.
         * @param[in] tuple The input tuple.
         * @param[in] factor The multiplication factor.
         * @return New object containing the result.
         */
        inline ColourTupleRGB
        operator*(const ColourTupleRGB& tuple, interp_channel_t factor);

        /**
         * @brief Multiplication with a constant.
         * @param[in] factor The multiplication factor.
         * @param[in] tuple The input tuple.
         * @return New object containing the result.
         */
        inline ColourTupleRGB
        operator*(interp_channel_t factor, const ColourTupleRGB& tuple);

        /**
         * @brief Multiplication of two tuples' values.
         * @note The multiplication is done element-wise.
         * @param[in] tuple1 The first input tuple.
         * @param[in] tuple2 The second input tuple.
         * @return New object containing the result.
         */
        inline ColourTupleRGB
        operator*(const ColourTupleRGB& tuple1, const ColourTupleRGB& tuple2);

        /**
         * @brief Addition of two tuples.
         * @param[in] tuple1 The first input tuple.
         * @param[in] tuple2 The second input tuple.
         * @return New object containing the result.
         */
        inline ColourTupleRGB
        operator+(const ColourTupleRGB& tuple1, const ColourTupleRGB& tuple2);


        /* ****************************************
         * RGBA
         * **************************************** */

        struct CoordTupleRGBA;

        /**
         * @brief A 4-tuple of RGBA channel/colour values.
         */
        struct ColourTupleRGBA
        {
            /**
             * @brief The corresponding coordinates tuple type.
             */
            typedef CoordTupleRGBA coord_tuple_t;

            /**
                * @brief Constructor.
                * @note All members are set to 0.
                */
            ColourTupleRGBA()
                    : val_r(0),
                    val_g(0),
                    val_b(0),
                    val_a(0)
            {
                //NIL
            }

            /**
             * @brief Multiplication with values from another tuple.
             * @note The multiplication is done element-wise.
             * @param[in] other The other tuple.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTupleRGBA& operator*=(const ColourTupleRGBA& other);

            /**
             * @brief Multiplication with a constant.
             * @param[in] factor The multiplication factor.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTupleRGBA& operator*=(interp_channel_t factor);

            /**
             * @brief Addition of values from another tuple.
             * @param[in] other The other tuple.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTupleRGBA& operator+=(const ColourTupleRGBA& other);

            /**
             * The 'red' value.
             */
            interp_channel_t val_r;

            /**
             * The 'green' value.
             */
            interp_channel_t val_g;

            /**
             * The 'blue' value.
             */
            interp_channel_t val_b;

            /**
             * The 'alpha' value.
             */
            interp_channel_t val_a;

        }; // ColourTupleRGBA

        /**
         * @brief Multiplication with a constant.
         * @param[in] tuple The input tuple.
         * @param[in] factor The multiplication factor.
         * @return New object containing the result.
         */
        inline ColourTupleRGBA
        operator*(const ColourTupleRGBA& tuple, interp_channel_t factor);

        /**
         * @brief Multiplication with a constant.
         * @param[in] factor The multiplication factor.
         * @param[in] tuple The input tuple.
         * @return New object containing the result.
         */
        inline ColourTupleRGBA
        operator*(interp_channel_t factor, const ColourTupleRGBA& tuple);

        /**
         * @brief Multiplication of two tuples' values.
         * @note The multiplication is done element-wise.
         * @param[in] tuple1 The first input tuple.
         * @param[in] tuple2 The second input tuple.
         * @return New object containing the result.
         */
        inline ColourTupleRGBA
        operator*(const ColourTupleRGBA& tuple1, const ColourTupleRGBA& tuple2);

        /**
         * @brief Addition of two tuples.
         * @param[in] tuple1 The first input tuple.
         * @param[in] tuple2 The second input tuple.
         * @return New object containing the result.
         */
        inline ColourTupleRGBA
        operator+(const ColourTupleRGBA& tuple1, const ColourTupleRGBA& tuple2);

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr

#include <photoropter/colour_tuple.inl.h>

#endif // __PHTR__COLOUR_TUPLE_H__
