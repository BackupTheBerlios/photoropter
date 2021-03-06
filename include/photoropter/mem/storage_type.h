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

#ifndef PHTR_STORAGE_TYPE_H__
#define PHTR_STORAGE_TYPE_H__

extern "C"
{
#include <stdint.h>
}

namespace phtr
{
    namespace mem
    {

        /**
         * @brief Struct listing image storage types.
         * @note The struct contains an enum which defines the actual channels.
         */
        struct Storage
        {

            /**
            * @brief The enum containing the actual storage types.
            */
            enum type
            {

                /**
                * @brief Unknown type.
                */
                unknown = 0,
                /**
                * @brief 8 bit unsigned RGB, interleaved.
                */
                rgb_8_inter,
                /**
                * @brief 16 bit unsigned RGB, interleaved.
                */
                rgb_16_inter,
                /**
                * @brief 32 bit unsigned RGB, interleaved.
                */
                rgb_32_inter,
                /**
                * @brief 8 bit unsigned RGB, planar.
                */
                rgb_8_planar,
                /**
                * @brief 16 bit unsigned RGB, planar.
                */
                rgb_16_planar,
                /**
                * @brief 32 bit unsigned RGB, planar.
                */
                rgb_32_planar,
                /**
                * @brief 8 bit unsigned RGBA, interleaved.
                */
                rgba_8_inter,
                /**
                * @brief 16 bit unsigned RGBA, interleaved.
                */
                rgba_16_inter,
                /**
                * @brief 32 bit unsigned RGBA, interleaved.
                */
                rgba_32_inter,
                /**
                * @brief 8 bit unsigned RGBA, planar.
                */
                rgba_8_planar,
                /**
                * @brief 16 bit unsigned RGBA, planar.
                */
                rgba_16_planar,
                /**
                * @brief 32 bit unsigned RGBA, planar.
                */
                rgba_32_planar

            }; // enum Storage::type

        }; // class Storage

    } // namespace phtr::mem

} // namespace phtr

#endif // PHTR_STORAGE_TYPE_H__
