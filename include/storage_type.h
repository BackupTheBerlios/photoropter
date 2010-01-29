#ifndef __STORAGETYPES_H__
#define __STORAGETYPES_H__

namespace std
{
#include <stdint.h>
}

namespace phtr
{
    /**
    * \brief Struct containing image storage types.
    */
    struct Storage
    {

        /**
        * \brief The enum containing the actual storage types.
        */
        enum type
        {
            /**
            * \brief Unknown type.
            */
            unknown = 0,
            /**
            * \brief 8 bit unsigned RGB, interleaved.
            */
            rgb_8_inter,
            /**
            * \brief 16 bit unsigned RGB, interleaved.
            */
            rgb_16_inter,
            /**
            * \brief 32 bit unsigned RGB, interleaved.
            */
            rgb_32_inter,
            /**
            * \brief 8 bit unsigned RGB, planar.
            */
            rgb_8_planar,
            /**
            * \brief 16 bit unsigned RGB, planar.
            */
            rgb_16_planar,
            /**
            * \brief 32 bit unsigned RGB, planar.
            */
            rgb_32_planar
        }; // enum Storage::type

    }; // class Storage

} // namespace phtr

#endif // __STORAGETYPES_H__
