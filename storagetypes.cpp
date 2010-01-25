#include "storagetypes.h"

namespace phtr
{

    namespace storage
    {
        type get_type(int bits, bool alpha, bool interleaved)
        {
            type ret = unknown;

            if (bits == 8)
            {
                if (alpha)
                {
                    ret = interleaved ? rgba_8_inter : rgba_8_planar;
                }
                else
                {
                    ret = interleaved ? rgb_8_inter : rgb_8_planar;
                }
            }
            else if (bits == 16)
            {
                if (alpha)
                {
                    ret = interleaved ? rgba_16_inter : rgba_16_planar;
                }
                else
                {
                    ret = interleaved ? rgb_16_inter : rgb_16_planar;
                }
            }
            else if (bits == 32)
            {
                if (alpha)
                {
                    ret = interleaved ? rgba_32_inter : rgba_32_planar;
                }
                else
                {
                    ret = interleaved ? rgb_32_inter : rgb_32_planar;
                }
            }

            return ret;
        }

    } // namespace storage

} // namespace phtr
