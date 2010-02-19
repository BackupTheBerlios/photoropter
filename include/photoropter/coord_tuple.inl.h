/*
 * coord_tuple.inl.h
 *
 *  Created on: 19.02.2010
 *      Author: robert
 */

namespace phtr
{

    namespace mem
    {

        CoordTupleRGB::CoordTupleRGB(const CoordTupleRGB& orig)
        {
            for (size_t i = 0; i < colour_tuple_t::num_vals; ++i)
            {
                x[i] = orig.x[i];
                y[i] = orig.y[i];
            }
        }

        CoordTupleRGB& CoordTupleRGB::operator=(const CoordTupleRGB& orig)
        {
            for (size_t i = 0; i < colour_tuple_t::num_vals; ++i)
            {
                x[i] = orig.x[i];
                y[i] = orig.y[i];
            }

            return *this;
        }

    } // namespace phtr::mem

} // namespace phtr
