#include "exception.h"

namespace phr
{

    namespace exception
    {

        base_exception::base_exception(const std::string& msg)
                : std::exception(),
                msg_(msg)
        {
        }

        base_exception::~base_exception() throw ()
        {
            // NIL
        }

        const char* base_exception::what() throw ()
        {
            return msg_.c_str();
        }

        not_implemented::not_implemented(const std::string& msg)
                : base_exception(msg)
        {
            // NIL
        }

    } // namespace exception

} // namespace phr
