#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

namespace phtr
{

    namespace exception
    {

        class base_exception : public std::exception
        {

            public:
                base_exception(const std::string& msg);
                virtual ~base_exception() throw();

                virtual const char* what() throw();

            private:
                const std::string msg_;
        };

        class not_implemented: public base_exception
        {

            public:
                not_implemented(const std::string& msg);
        };

    } // namespace exception

} // namespace phtr

#endif // __EXCEPTION_H__
