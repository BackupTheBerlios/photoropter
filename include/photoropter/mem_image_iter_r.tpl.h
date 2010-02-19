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

    template <mem::Storage::type T>
    MemImageIterR<T>::MemImageIterR
    (channel_storage_t* base_addr, size_t px_offs, size_t step, size_t line_step,
     size_t r_offs, size_t g_offs, size_t b_offs, size_t a_offs)
            : MemImageIterBase<T>(const_cast<channel_storage_t*>(base_addr), px_offs,
                                  step, line_step, r_offs, g_offs, b_offs, a_offs)
    {
        //NIL
    }

    template <mem::Storage::type T>
    typename MemImageIterR<T>::channel_storage_t
    MemImageIterR<T>::get_px_val(Channel::type channel)
    {
        switch (channel)
        {
            case Channel::red:
            default:
                return this->base_addr_[this->px_offs_ + this->r_offs_];
                break;

            case Channel::green:
                return this->base_addr_[this->px_offs_ + this->g_offs_];
                break;

            case Channel::blue:
                return this->base_addr_[this->px_offs_ + this->b_offs_];
                break;

            case Channel::alpha:
                return this->base_addr_[this->px_offs_ + this->a_offs_];
                break;
        }
    }


} // namespace phtr
