#ifndef __STORAGETYPES_H__
#define __STORAGETYPES_H__

namespace phtr
{

    namespace storage
    {

        enum type
        {
            unknown,
            rgb_8_inter,
            rgba_8_inter,
            rgb_16_inter,
            rgba_16_inter,
            rgb_32_inter,
            rgba_32_inter,
            rgb_8_planar,
            rgba_8_planar,
            rgb_16_planar,
            rgba_16_planar,
            rgb_32_planar,
            rgba_32_planar
        }; // enum storage::type

        type get_type(int bits, bool alpha, bool interleaved);

    } // namespace storage

} // namespace phtr

#endif // __STORAGETYPES_H__
