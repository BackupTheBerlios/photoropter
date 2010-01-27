#include "storagetypes.h"

namespace phtr
{

    Storage::type Storage::get_type_dontuse (int bits, bool interleaved)
    {
        type ret = unknown;

        if (bits == 8)
        {
            ret = interleaved ? rgb_8_inter : rgb_8_planar;
        }

        else if (bits == 16)
        {
            ret = interleaved ? rgb_16_inter : rgb_16_planar;
        }

        else if (bits == 32)
        {
            ret = interleaved ? rgb_32_inter : rgb_32_planar;
        }

        return ret;
    }

} // namespace phtr
