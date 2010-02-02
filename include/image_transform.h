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

#ifndef __IMAGE_TRANSFORM_H__
#define __IMAGE_TRANSFORM_H__

#include <memory>

namespace phtr
{

    template <typename interpolator_t, typename image_view_w_t>
    class ImageTransform
    {

        public:
            typedef typename interpolator_t::image_view_t image_view_t;

        public:
            ImageTransform(const image_view_t& image_view_r, image_view_w_t& image_view_w);

        public:
            ~ImageTransform();

        public:
            void do_transform();

        private:
            interpolator_t interpolator_;

        private:
            image_view_w_t& image_view_w_;

    }; // class ImageTransform

} // namespace phtr

#include "image_transform.tpl.h"

#endif // __IMAGE_TRANSFORM_H__
