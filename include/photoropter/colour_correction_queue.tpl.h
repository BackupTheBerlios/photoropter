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

    template <typename coord_tuple_T>
    void ColourCorrectionQueue::get_correction_factors(const coord_tuple_T& coords,
            typename coord_tuple_T::channel_order_t::colour_tuple_t& factors) const
    {

        for (size_t i = 0; i < mem::ColourTupleRGB::num_vals; ++i)
        {
            factors.value[i] = 1.0;
        }

        mem::ColourTupleRGB tmp_factors;

        for (size_t i = 0; i < n_models_; ++i)
        {
            correction_model_[i]->get_correction_factors(coords, tmp_factors);
            factors *= tmp_factors;
        }

    }

} // namespace phtr
