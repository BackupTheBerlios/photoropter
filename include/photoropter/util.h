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

#ifndef __PHTR_UTIL_H__
#define __PHTR_UTIL_H__

namespace phtr
{
    /**
    * @brief Utility classes and helper functions.
    */
    namespace util
    {

        ///@cond PROTECTED

        /**
        * @brief Class to set a list of parameters in an easy way.
        * @param iter_t The iteration type.
        */
        template <class iter_t>
        class SetParam
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief The value type of the parameter list.
                */
                typedef typename iter_t::value_type value_t;

            public:
                /**
                * @brief Constructor.
                * @param[in] pos The current position.
                */
                SetParam(const iter_t& pos)
                        : pos_(pos)
                {
                    //NIL
                }

            public:
                /**
                * @brief Set a value.
                * @details Sets the 'current' value and returns a SetParam instance pointing to the
                * next parameter.
                * @param[in] val The value.
                * @return SetParam object pointing to the next parameter.
                */
                SetParam operator()(const value_t& val)
                {
                    *pos_ = val;
                    ++pos_;

                    return *this;
                }

                /* ****************************************
                 * internals
                 * **************************************** */

            private:
                /**
                * @brief The current position.
                */
                iter_t pos_;

        }; // template class SetParam<>

        ///@endcond

    } // namespace phtr::util
} // namespace phtr

#endif // __PHTR_UTIL_H__
