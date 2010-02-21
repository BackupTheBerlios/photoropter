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

#include <photoropter/mem/mem_layout.h>
#include <photoropter/mem/channel_type.h>

namespace phtr
{

    namespace mem
    {

        ///@cond PROTECTED

        size_t ChannelOrderRGB::get_channel_index(Channel::type chan_type)
        {
            switch (chan_type)
            {
                case Channel::red:
                default:
                    return 0;
                    break;

                case Channel::green:
                    return 1;
                    break;

                case Channel::blue:
                    return 2;
                    break;
            }
        }

        const Channel::type ChannelOrderRGB::channel_type[] = {Channel::red, Channel::green, Channel::blue};

        const size_t ChannelOrderRGB::idx_red = 0;

        const size_t ChannelOrderRGB::idx_green = 1;

        const size_t ChannelOrderRGB::idx_blue = 2;

        const size_t ChannelOrderRGB::idx_alpha = 0;

        size_t ChannelOrderRGBA::get_channel_index(Channel::type chan_type)
        {
            switch (chan_type)
            {
                case Channel::red:
                default:
                    return 0;
                    break;

                case Channel::green:
                    return 1;
                    break;

                case Channel::blue:
                    return 2;
                    break;

                case Channel::alpha:
                    return 3;
                    break;
            }
        }

        const Channel::type ChannelOrderRGBA::channel_type[] = {Channel::red, Channel::green, Channel::blue, Channel::alpha};

        const size_t ChannelOrderRGBA::idx_red = 0;

        const size_t ChannelOrderRGBA::idx_green = 1;

        const size_t ChannelOrderRGBA::idx_blue = 2;

        const size_t ChannelOrderRGBA::idx_alpha = 3;

        ///@endcond

    } // namespace phtr::mem

} // namespace phtr
