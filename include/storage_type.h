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

#ifndef __STORAGE_TYPE_H__
#define __STORAGE_TYPE_H__

namespace std
{
extern "C" {
#include <stdint.h>
}
}

namespace phtr
{
    /**
    * \brief Struct containing image storage types.
    */
    struct Storage
    {

        /**
        * \brief The enum containing the actual storage types.
        */
        enum type
        {
            /**
            * \brief Unknown type.
            */
            unknown = 0,
            /**
            * \brief 8 bit unsigned RGB, interleaved.
            */
            rgb_8_inter,
            /**
            * \brief 16 bit unsigned RGB, interleaved.
            */
            rgb_16_inter,
            /**
            * \brief 32 bit unsigned RGB, interleaved.
            */
            rgb_32_inter,
            /**
            * \brief 8 bit unsigned RGB, planar.
            */
            rgb_8_planar,
            /**
            * \brief 16 bit unsigned RGB, planar.
            */
            rgb_16_planar,
            /**
            * \brief 32 bit unsigned RGB, planar.
            */
            rgb_32_planar
        }; // enum Storage::type

    }; // class Storage

} // namespace phtr

#endif // __STORAGE_TYPE_H__
