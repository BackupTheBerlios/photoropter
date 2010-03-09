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

#include <photoropter/auto_scaler.h>

namespace phtr
{

    IAutoScaler* get_auto_scaler(mem::Storage::type storage_type, const IImageTransform& image_transform)
    {
        switch (storage_type)
        {
            case mem::Storage::rgb_8_inter:
            default:
                return new AutoScalerRGB(image_transform);
                break;

            case mem::Storage::rgb_16_inter:
                return new AutoScalerRGB(image_transform);
                break;

            case mem::Storage::rgb_32_inter:
                return new AutoScalerRGB(image_transform);
                break;

            case mem::Storage::rgba_8_inter:
                return new AutoScalerRGBA(image_transform);
                break;

            case mem::Storage::rgba_16_inter:
                return new AutoScalerRGBA(image_transform);
                break;

            case mem::Storage::rgba_32_inter:
                return new AutoScalerRGBA(image_transform);
                break;
        }
    }

} // namespace phtr
