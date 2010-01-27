#ifndef __STORAGETYPES_H__
#define __STORAGETYPES_H__

namespace phtr
{
    /**
    * \brief Class containing image storage types.
    */

    class Storage
    {

        public:
            /**
            * \brief The enum containing the actual storage types.
            */
            enum type
            {
                unknown,
                rgb_8_inter,
                rgb_16_inter,
                rgb_32_inter,
                rgb_8_planar,
                rgb_16_planar,
                rgb_32_planar
            }; // enum storage::type

            static type get_type_dontuse (int bits, bool interleaved);

    }; // class Storage

} // namespace phtr

#endif // __STORAGETYPES_H__
