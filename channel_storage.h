#ifndef __CHANNEL_STORAGE_H__
#define __CHANNEL_STORAGE_H__

#include "storagetypes.h"

namespace phtr
{

    /**
     * \brief Template for determining the channel storage type
     * to a given \ref Storage::type.
     * \details This template \em has to be
     * specialised for every supported type. In each specialisation,
     * a member typedef 'type' has to be provided.
     */
    template <Storage::type T>
    struct ChannelStorage
    {
    }; // template struct ChannelStorage

    /**
    * \brief Specialisation of \ref ChannelStorage for \ref Storage::rgb_8_inter.
    */
    template <>
    struct ChannelStorage<Storage::rgb_8_inter>
    {

        typedef std::uint8_t type;

    }; // template struct ChannelStorage<Storage::rgb_8_inter>

    /**
    * \brief Specialisation of \ref ChannelStorage for \ref Storage::rgb_16_inter.
    */
    template <>
    struct ChannelStorage<Storage::rgb_16_inter>
    {

        typedef std::uint16_t type;

    }; // template struct ChannelStorage<Storage::rgb_16_inter>

    /**
    * \brief Specialisation of \ref ChannelStorage for \ref Storage::rgb_32_inter.
    */
    template <>
    struct ChannelStorage<Storage::rgb_32_inter>
    {

        typedef std::uint32_t type;

    }; // template struct ChannelStorage<Storage::rgb_32_inter>

    /**
    * \brief Specialisation of \ref ChannelStorage for \ref Storage::rgb_8_planar.
    */
    template <>
    struct ChannelStorage<Storage::rgb_8_planar>
    {

        typedef std::uint8_t type;

    }; // template struct ChannelStorage<Storage::rgb_8_planar>

    /**
    * \brief Specialisation of \ref ChannelStorage for \ref Storage::rgb_16_planar.
    */
    template <>
    struct ChannelStorage<Storage::rgb_16_planar>
    {

        typedef std::uint16_t type;

    }; // template struct ChannelStorage<Storage::rgb_16_planar>

    /**
    * \brief Specialisation of \ref ChannelStorage for \ref Storage::rgb_32_planar.
    */
    template <>
    struct ChannelStorage<Storage::rgb_32_planar>
    {

        typedef std::uint32_t type;

    }; // template struct ChannelStorage<Storage::rgb_32_planar>


} // namespace phtr

#endif // __CHANNEL_STORAGE_H__
