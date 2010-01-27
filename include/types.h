#ifndef __TYPES_H__
#define __TYPES_H__

#include <memory>
#include <cstddef>

#ifdef USE_BOOST_SCOPED_PTR
#include <boost/scoped_ptr.hpp>
#endif // USE_BOOST_SCOPED_PTR

namespace phtr
{

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
    * \brief Class containing channel designations.
    * \note The class contains an enum which defines the actual channels.
    */

    struct Channel
    {

        /**
        * \brief The actual enum containing channel designations.
        */
        enum type
        {
            red = 0,
            green,
            blue
        };

    }; // class Channel

} // namespace phtr

#endif // __TYPES_H__
