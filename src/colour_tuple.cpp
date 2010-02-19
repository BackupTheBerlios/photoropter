/*
 * colour_tuple.cpp
 *
 *  Created on: 19.02.2010
 *      Author: robert
 */

#include <photoropter/colour_tuple.h>

namespace phtr
{

    namespace mem
    {

        const size_t ColourTupleRGB::num_vals = 3;

        const Channel::type ColourTupleRGB::channel_type[] = {Channel::red, Channel::green, Channel::blue};

    } // namespace phtr::mem

} // namespace phtr
