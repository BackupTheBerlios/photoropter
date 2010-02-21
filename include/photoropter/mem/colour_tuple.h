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
#include <photoropter/mem/channel_type.h>
#include <photoropter/mem/mem_layout.h>

namespace phtr
{

    namespace mem
    {

        /**
         * @brief The maximal number of channels supported (i.e., 4).
         */
        static const size_t PHTR_MAX_CHANNELS = 4;

        ///@cond PROTECTED

        /* ****************************************
         * RGB
         * **************************************** */

        /**
         * @brief A tuple of RGB(A) channel/colour values.
         */
        template <typename channel_order_T, size_t num_vals_T>
        struct ColourTuple
        {
            /**
             * @brief Channel order information.
             */
            typedef channel_order_T channel_order_t;

            /**
             * @brief Constructor.
             */
            ColourTuple()
            {
                //NIL
            }

            /**
             * @brief Copy constructor.
             * @param[in] orig The original object.
             */
            inline ColourTuple(const ColourTuple& orig);

            /**
             * @brief Assignment
             * @param[in] orig The original object.
             * @return Reference to the current object.
             */
            inline ColourTuple& operator=(const ColourTuple& orig);

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
            inline ColourTuple& operator*=(const ColourTuple& other);

            /**
             * @brief Multiplication with a constant.
             * @param[in] factor The multiplication factor.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTuple& operator*=(interp_channel_t factor);

            /**
             * @brief Addition of values from another tuple.
             * @param[in] other The other tuple.
             * @return (Self-)Reference to the current object.
             */
            inline ColourTuple& operator+=(const ColourTuple& other);

            /**
             * The array of values;
             */
            interp_channel_t value[num_vals_T];

            /**
             * The number of values (i.e., 3).
             */
            static const size_t num_vals;

        }; // template struct ColourTuple

        /**
         * @brief A 3-colour (RGB) tuple.
         */
        typedef ColourTuple<ChannelOrderRGB, 3> ColourTupleRGB;

        /**
         * @brief A 4-colour (RGBA) tuple.
         */
        typedef ColourTuple<ChannelOrderRGBA, 4> ColourTupleRGBA;

        /**
         * @brief Multiplication with a constant.
         * @param[in] tuple The input tuple.
         * @param[in] factor The multiplication factor.
         * @return New object containing the result.
         */
        template <typename channel_order_T, size_t num_vals_T>
        inline ColourTuple<channel_order_T, num_vals_T>
        operator*(const ColourTuple<channel_order_T, num_vals_T>& tuple, interp_channel_t factor);

        /**
         * @brief Multiplication with a constant.
         * @param[in] factor The multiplication factor.
         * @param[in] tuple The input tuple.
         * @return New object containing the result.
         */
        template <typename channel_order_T, size_t num_vals_T>
        inline ColourTuple<channel_order_T, num_vals_T>
        operator*(interp_channel_t factor, const ColourTuple<channel_order_T, num_vals_T>& tuple);

        /**
         * @brief Multiplication of two tuples' values.
         * @note The multiplication is done element-wise.
         * @param[in] tuple1 The first input tuple.
         * @param[in] tuple2 The second input tuple.
         * @return New object containing the result.
         */
        template <typename channel_order_T, size_t num_vals_T>
        inline ColourTuple<channel_order_T, num_vals_T>
        operator*(const ColourTuple<channel_order_T, num_vals_T>& tuple1,
                  const ColourTuple<channel_order_T, num_vals_T>& tuple2);

        /**
         * @brief Addition of two tuples.
         * @param[in] tuple1 The first input tuple.
         * @param[in] tuple2 The second input tuple.
         * @return New object containing the result.
         */
        template <typename channel_order_T, size_t num_vals_T>
        inline ColourTuple<channel_order_T, num_vals_T>
        operator+(const ColourTuple<channel_order_T, num_vals_T>& tuple1,
                  const ColourTuple<channel_order_T, num_vals_T>& tuple2);

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr

#include <photoropter/mem/colour_tuple.tpl.h>

#endif // __PHTR__COLOUR_TUPLE_H__
