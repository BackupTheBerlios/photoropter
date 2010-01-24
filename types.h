#ifndef __TYPES_H__
#define __TYPES_H__

#include <memory>
#include <cstddef>

#ifdef USE_BOOST_SCOPED_PTR
#include <boost/scoped_ptr.hpp>
#endif // USE_BOOST_SCOPED_PTR

namespace phr
{

    class basic_image_impl;

#ifdef USE_BOOST_SCOPED_PTR
    typedef boost::scoped_ptr<basic_image_impl> img_sptr_t;
#else
    typedef std::auto_ptr<basic_image_impl> img_sptr_t;
#endif // USE_BOOST_SCOPED_PTR

    /**
    * \brief Channel value type.
    */
    typedef double channel_t;

    /**
    * \brief Coordinate type.
    */
    typedef size_t coord_t;

    /**
    * \brief Type for interpolated coordinates.
    */
    typedef double interp_coord_t;

    /**
    * \brief Namespace containing channel designations.
    * The namespace contains an enum which defines the actual channels.
    */

    namespace channel
    {
        /**
        * \brief The actual enum containing channel designations.
        */
        enum type
        {
            red = 0,
            green,
            blue,
            alpha
        };
    }

} // namespace phr

#endif // __TYPES_H__
