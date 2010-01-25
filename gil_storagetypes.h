#ifndef __GIL_STORAGETYPES_H__
#define __GIL_STORAGETYPES_H__

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include "storagetypes.h"

namespace phtr
{

    template <storage::type t>
    struct gil_storage
    {
        typedef void type;
    };

    template <>
    struct gil_storage<storage::rgb_8_inter>
    {
        typedef boost::gil::rgb8_image_t type;
    };

    template <>
    struct gil_storage<storage::rgba_8_inter>
    {
        typedef boost::gil::rgba8_image_t type;
    };

    template <>
    struct gil_storage<storage::rgb_16_inter>
    {
        typedef boost::gil::rgb16_image_t type;
    };

    template <>
    struct gil_storage<storage::rgba_16_inter>
    {
        typedef boost::gil::rgba16_image_t type;
    };

    template <>
    struct gil_storage<storage::rgb_32_inter>
    {
        typedef boost::gil::rgb32_image_t type;
    };

    template <>
    struct gil_storage<storage::rgba_32_inter>
    {
        typedef boost::gil::rgba32_image_t type;
    };

    template <>
    struct gil_storage<storage::rgb_8_planar>
    {
        typedef boost::gil::rgb8_image_t type;
    };

    template <>
    struct gil_storage<storage::rgba_8_planar>
    {
        typedef boost::gil::rgba8_image_t type;
    };

    template <>
    struct gil_storage<storage::rgb_16_planar>
    {
        typedef boost::gil::rgb16_image_t type;
    };

    template <>
    struct gil_storage<storage::rgba_16_planar>
    {
        typedef boost::gil::rgba16_image_t type;
    };

    template <>
    struct gil_storage<storage::rgb_32_planar>
    {
        typedef boost::gil::rgb32_image_t type;
    };

    template <>
    struct gil_storage<storage::rgba_32_planar>
    {
        typedef boost::gil::rgba32_image_t type;
    };

} // namespace phtr

#endif // __GIL_STORAGETYPES_H__
