#include "exception.h"

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

        base_exception::~base_exception() throw()
        {
            //NIL
        }

        const char* base_exception::what() const throw()
        {
            std::string tmp = prefix_;
            if (not msg_.empty())
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
