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

    namespace mem
    {

        ///@cond PROTECTED


        /* ****************************************
         * Generic
         * **************************************** */

        template <typename channel_order_T, size_t num_vals_T>
        const size_t ColourTuple<channel_order_T, num_vals_T>::num_vals = num_vals_T;

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>::
        ColourTuple(const ColourTuple<channel_order_T, num_vals_T>& orig)
        {
            for (size_t i = 0; i < num_vals; ++i)
            {
                value[i] = orig.value[i];
            }
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>&
        ColourTuple<channel_order_T, num_vals_T>::
        operator=(const ColourTuple<channel_order_T, num_vals_T>& orig)
        {
            for (size_t i = 0; i < num_vals; ++i)
            {
                value[i] = orig.value[i];
            }

            return *this;
        }

        template <typename channel_order_T, size_t num_vals_T>
        void
        ColourTuple<channel_order_T, num_vals_T>::
        clear()
        {
            for (size_t i = 0; i < num_vals; ++i)
            {
                value[i] = 0.0;
            }
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>&
        ColourTuple<channel_order_T, num_vals_T>::
        operator*=(const ColourTuple<channel_order_T, num_vals_T>& other)
        {
            for (size_t i = 0; i < num_vals; ++i)
            {
                value[i] *= other.value[i];
            }

            return *this;
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>&
        ColourTuple<channel_order_T, num_vals_T>::
        operator*=(interp_channel_t factor)
        {
            for (size_t i = 0; i < num_vals; ++i)
            {
                value[i] *= factor;
            }

            return *this;
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>&
        ColourTuple<channel_order_T, num_vals_T>::
        operator+=(const ColourTuple<channel_order_T, num_vals_T>& other)
        {
            for (size_t i = 0; i < num_vals; ++i)
            {
                value[i] += other.value[i];
            }

            return *this;
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>
        operator*(const  ColourTuple<channel_order_T, num_vals_T>& tuple, interp_channel_t factor)
        {
            ColourTupleRGB ret(tuple);

            for (size_t i = 0; i < ColourTupleRGB::num_vals; ++i)
            {
                ret.value[i] *= factor;
            }

            return ret;
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>
        operator*(interp_channel_t factor, const ColourTuple<channel_order_T, num_vals_T>& tuple)
        {
            ColourTuple<channel_order_T, num_vals_T> ret(tuple);

            for (size_t i = 0; i < ColourTuple<channel_order_T, num_vals_T>::num_vals; ++i)
            {
                ret.value[i] *= factor;
            }

            return ret;
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>
        operator*(const ColourTuple<channel_order_T, num_vals_T>& tuple1,
                  const ColourTuple<channel_order_T, num_vals_T>& tuple2)
        {
            ColourTuple<channel_order_T, num_vals_T> ret(tuple1);

            for (size_t i = 0; i < ColourTuple<channel_order_T, num_vals_T>::num_vals; ++i)
            {
                ret.value[i] *= tuple2.value[i];
            }

            return ret;
        }

        template <typename channel_order_T, size_t num_vals_T>
        ColourTuple<channel_order_T, num_vals_T>
        operator+(const ColourTuple<channel_order_T, num_vals_T>& tuple1,
                  const ColourTuple<channel_order_T, num_vals_T>& tuple2)
        {
            ColourTuple<channel_order_T, num_vals_T> ret(tuple1);

            for (size_t i = 0; i < ColourTuple<channel_order_T, num_vals_T>::num_vals; ++i)
            {
                ret.value[i] += tuple2.value[i];
            }

            return ret;
        }

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr
