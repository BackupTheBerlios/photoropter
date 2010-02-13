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

#ifndef __PHTR_EXCEPTION_H__
#define __PHTR_EXCEPTION_H__

#include <string>

namespace phtr
{

    namespace exception
    {

        /**
        * @brief Base exception class.
        */
        class base_exception : public std::exception
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief The message associated with the exception.
                * @details This message contains the general type of exception,
                * and possibly a further explanation of the cause.
                * @return The message.
                */
                virtual const char* what() const throw();

            public:
                /**
                * @brief Destructor.
                */
                virtual ~base_exception() throw();

                /* ****************************************
                 * internals
                 * **************************************** */

            protected:
                /**
                * @brief Standard constructor.
                */
                base_exception();

            protected:
                /**
                * @brief Construction with a specific message.
                * @param[in] msg The message.
                */
                base_exception(const std::string& msg);

            protected:
                /**
                * @brief Internal message prefix.
                */
                std::string prefix_;

            private:
                /**
                * @brief Internal string containing the exception message.
                */
                std::string msg_;

        }; // class base_exception

        /**
        * @brief Exception that is thrown when a particular feature of a class
        * is not implemented (yet).
        */
        class not_implemented: public base_exception
        {

            public:
                /**
                * @brief Standard constructor.
                */
                not_implemented();

            public:
                /**
                * @brief Construction with a specific message.
                * @param[in] msg The message.
                */
                not_implemented(const std::string& msg);

        };

        /**
        * @brief Exception that is thrown when a function argument is illegal
        * (e.g., parameter out of range).
        */
        class illegal_argument: public base_exception
        {

            public:
                /**
                * @brief Standard constructor.
                */
                illegal_argument();

            public:
                /**
                * @brief Construction with a specific message.
                * @param[in] msg The message.
                */
                illegal_argument(const std::string& msg);

        };

    } // namespace exception

} // namespace phtr

#endif // __PHTR_EXCEPTION_H__
