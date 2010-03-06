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

#include <photoropter/exception.h>

namespace phtr
{

    namespace exception
    {

        base_exception::base_exception(const std::string& msg)
                : std::exception(),
                prefix_("Exception"),
                msg_(msg)
        {
        }

        base_exception::base_exception()
        {
            //NIL
        }

        base_exception::~base_exception() throw()
        {
            //NIL
        }

        const char* base_exception::what() const throw()
        {
            std::string tmp = prefix_;
            if (!msg_.empty())
            {
                tmp += ": " + msg_;
            }

            return tmp.c_str();
        }

        not_implemented::not_implemented()
        {
            //NIL
        }

        not_implemented::not_implemented(const std::string& msg)
                : base_exception(msg)
        {
            prefix_ = "Feature not implemented";
        }

        illegal_argument::illegal_argument()
        {
            //NIL
        }

        illegal_argument::illegal_argument(const std::string& msg)
                : base_exception(msg)
        {
            prefix_ = "Illegal argument";
        }

    } // namespace exception

} // namespace phtr
