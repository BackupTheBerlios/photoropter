/*

Photoropter: lens correction for digital cameras

Copyright (c) 2010 Robert Fendt

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef __PHTR_CHANNEL_STORAGE_H__
#define __PHTR_CHANNEL_STORAGE_H__

#include <photoropter/storage_type.h>
#include <cstddef>

namespace phtr
{
    namespace mem
    {

        /**
         * @brief Template for determining the channel storage type
         * to a given @ref Storage::type.
         * @details This template @em has to be
         * specialised for every supported type. In each specialisation,
         * a member typedef 'type' has to be provided.
         * @param T The storage type (e.g. @ref Storage::rgb_8_inter).
         */
        template <mem::Storage::type T>
        struct ChannelStorage
        {
            // provoke a compile-time error whenever this unspecialised version is used
            struct must_be_specialised_t;
            const size_t must_be_specialised;
            ChannelStorage() : must_be_specialised(sizeof(must_be_specialised_t)) {}
        }; // template struct ChannelStorage

        /**
        * @brief Specialisation of @ref ChannelStorage for @ref Storage::rgb_8_inter.
        */
        template <>
        struct ChannelStorage<Storage::rgb_8_inter>
        {

            /**
            * @brief The storage type.
            */
            typedef std::uint8_t type;

        }; // template struct ChannelStorage<Storage::rgb_8_inter>

        /**
        * @brief Specialisation of @ref ChannelStorage for @ref Storage::rgb_16_inter.
        */
        template <>
        struct ChannelStorage<Storage::rgb_16_inter>
        {

            /**
            * @brief The storage type.
            */
            typedef std::uint16_t type;

        }; // template struct ChannelStorage<Storage::rgb_16_inter>

        /**
        * @brief Specialisation of @ref ChannelStorage for @ref Storage::rgb_32_inter.
        */
        template <>
        struct ChannelStorage<Storage::rgb_32_inter>
        {

            /**
            * @brief The storage type.
            */
            typedef std::uint32_t type;

        }; // template struct ChannelStorage<Storage::rgb_32_inter>

        /**
        * @brief Specialisation of @ref ChannelStorage for @ref Storage::rgb_8_planar.
        */
        template <>
        struct ChannelStorage<Storage::rgb_8_planar>
        {

            /**
            * @brief The storage type.
            */
            typedef std::uint8_t type;

        }; // template struct ChannelStorage<Storage::rgb_8_planar>

        /**
        * @brief Specialisation of @ref ChannelStorage for @ref Storage::rgb_16_planar.
        */
        template <>
        struct ChannelStorage<Storage::rgb_16_planar>
        {

            /**
            * @brief The storage type.
            */
            typedef std::uint16_t type;

        }; // template struct ChannelStorage<Storage::rgb_16_planar>

        /**
        * @brief Specialisation of @ref ChannelStorage for @ref Storage::rgb_32_planar.
        */
        template <>
        struct ChannelStorage<Storage::rgb_32_planar>
        {

            /**
            * @brief The storage type.
            */
            typedef std::uint32_t type;

        }; // template struct ChannelStorage<Storage::rgb_32_planar>

    } // namespace phtr::mem

} // namespace phtr

#endif // __PHTR_CHANNEL_STORAGE_H__
