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

#ifndef PHTR_CHANNEL_RANGE_H__
#define PHTR_CHANNEL_RANGE_H__

#include <photoropter/mem/channel_storage.h>

namespace phtr
{

    namespace mem
    {

        ///@cond PROTECTED

        /**
        * @brief A struct template for accessing the minimal and maximal values of a
        * channel storage type. Uses std::numeric_limits.
        * @param storage_T The storage type (e.g. @ref Storage::rgb_8_inter).
        */
        template <Storage::type storage_T>
        struct ChannelRange
        {

        public:
            /**
            * @brief The channel storage type (e.g., uint8_t).
            */
            typedef typename ChannelStorage<storage_T>::type channel_storage_t;

        public:
            /**
            * @brief The minimal value a channel can store (e.g. 0 for unsigned types).
            * @return The min value.
            */
            static channel_storage_t min()
            {
                return std::numeric_limits<channel_storage_t>::min();
            }

        public:
            /**
            * @brief The maximal value a channel can store (e.g. 255 for uint8_t).
            * @return The max value.
            */
            static channel_storage_t max()
            {
                return std::numeric_limits<channel_storage_t>::max();
            }

        }; // namespace phtr

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr

#endif // PHTR_CHANNEL_RANGE_H__
