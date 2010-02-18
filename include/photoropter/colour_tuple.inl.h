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
         * RGB
         * **************************************** */


        ColourTupleRGB&
        ColourTupleRGB::
        operator*=(const ColourTupleRGB& other)
        {
            val_r *= other.val_r;
            val_g *= other.val_g;
            val_b *= other.val_b;

            return *this;
        }

        ColourTupleRGB&
        ColourTupleRGB::
        operator*=(interp_channel_t factor)
        {
            val_r *= factor;
            val_g *= factor;
            val_b *= factor;

            return *this;
        }

        ColourTupleRGB&
        ColourTupleRGB::
        operator+=(const ColourTupleRGB& other)
        {
            val_r += other.val_r;
            val_g += other.val_g;
            val_b += other.val_b;

            return *this;
        }

        ColourTupleRGB operator*(const ColourTupleRGB& tuple, interp_channel_t factor)
        {
            ColourTupleRGB ret(tuple);
            ret.val_r *= factor;
            ret.val_g *= factor;
            ret.val_b *= factor;

            return ret;
        }

        ColourTupleRGB operator*(interp_channel_t factor, const ColourTupleRGB& tuple)
        {
            ColourTupleRGB ret(tuple);
            ret.val_r *= factor;
            ret.val_g *= factor;
            ret.val_b *= factor;

            return ret;
        }

        ColourTupleRGB operator*(const ColourTupleRGB& tuple1, const ColourTupleRGB& tuple2)
        {
            ColourTupleRGB ret(tuple1);
            ret.val_r *= tuple2.val_r;
            ret.val_g *= tuple2.val_g;
            ret.val_b *= tuple2.val_b;

            return ret;
        }

        ColourTupleRGB operator+(const ColourTupleRGB& tuple1, const ColourTupleRGB& tuple2)
        {
            ColourTupleRGB ret(tuple1);
            ret.val_r += tuple2.val_r;
            ret.val_g += tuple2.val_g;
            ret.val_b += tuple2.val_b;

            return ret;
        }


        /* ****************************************
         * RGBA
         * **************************************** */


        ColourTupleRGBA&
        ColourTupleRGBA::
        operator*=(const ColourTupleRGBA& other)
        {
            val_r *= other.val_r;
            val_g *= other.val_g;
            val_b *= other.val_b;
            val_a *= other.val_a;

            return *this;
        }

        ColourTupleRGBA&
        ColourTupleRGBA::
        operator*=(interp_channel_t factor)
        {
            val_r *= factor;
            val_g *= factor;
            val_b *= factor;
            val_a *= factor;

            return *this;
        }

        ColourTupleRGBA&
        ColourTupleRGBA::
        operator+=(const ColourTupleRGBA& other)
        {
            val_r += other.val_r;
            val_g += other.val_g;
            val_b += other.val_b;
            val_a += other.val_a;

            return *this;
        }

        ColourTupleRGBA operator*(const ColourTupleRGBA& tuple, interp_channel_t factor)
        {
            ColourTupleRGBA ret(tuple);
            ret.val_r *= factor;
            ret.val_g *= factor;
            ret.val_b *= factor;
            ret.val_a *= factor;

            return ret;
        }

        ColourTupleRGBA operator*(interp_channel_t factor, const ColourTupleRGBA& tuple)
        {
            ColourTupleRGBA ret(tuple);
            ret.val_r *= factor;
            ret.val_g *= factor;
            ret.val_b *= factor;
            ret.val_a *= factor;

            return ret;
        }

        ColourTupleRGBA operator*(const ColourTupleRGBA& tuple1, const ColourTupleRGBA& tuple2)
        {
            ColourTupleRGBA ret(tuple1);
            ret.val_r *= tuple2.val_r;
            ret.val_g *= tuple2.val_g;
            ret.val_b *= tuple2.val_b;
            ret.val_a *= tuple2.val_a;

            return ret;
        }

        ColourTupleRGBA operator+(const ColourTupleRGBA& tuple1, const ColourTupleRGBA& tuple2)
        {
            ColourTupleRGBA ret(tuple1);
            ret.val_r += tuple2.val_r;
            ret.val_g += tuple2.val_g;
            ret.val_b += tuple2.val_b;
            ret.val_a += tuple2.val_a;

            return ret;
        }

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr
