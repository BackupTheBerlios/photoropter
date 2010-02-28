/*

  phtrtest: Photoropter demo application

  Copyright (C) 2010 Robert Fendt

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef PHTRTEST_VIL_PIXEL_TYPE_H__
#define PHTRTEST_VIL_PIXEL_TYPE_H__

#include <photoropter/mem/storage_type.h>

#include <vxl_config.h>
#include <vil/vil_rgb.h>
#include <vil/vil_rgba.h>

template <phtr::mem::Storage::type storage_T> struct VILPixelType;

template <>
struct VILPixelType<phtr::mem::Storage::rgb_8_inter>
{
    typedef vil_rgb<vxl_uint_8> vil_pixel_t;
    static const unsigned int num_components = 3;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgb_16_inter>
{
    typedef vil_rgb<vxl_uint_16> vil_pixel_t;
    static const unsigned int num_components = 3;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgb_32_inter>
{
    typedef vil_rgb<vxl_uint_32> vil_pixel_t;
    static const unsigned int num_components = 3;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgb_8_planar>
{
    typedef vil_rgb<vxl_uint_8> vil_pixel_t;
    static const unsigned int num_components = 3;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgb_16_planar>
{
    typedef vil_rgb<vxl_uint_16> vil_pixel_t;
    static const unsigned int num_components = 3;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgb_32_planar>
{
    typedef vil_rgb<vxl_uint_32> vil_pixel_t;
    static const unsigned int num_components = 3;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgba_8_inter>
{
    typedef vil_rgba<vxl_uint_8> vil_pixel_t;
    static const unsigned int num_components = 4;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgba_16_inter>
{
    typedef vil_rgba<vxl_uint_16> vil_pixel_t;
    static const unsigned int num_components = 4;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgba_32_inter>
{
    typedef vil_rgba<vxl_uint_32> vil_pixel_t;
    static const unsigned int num_components = 4;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgba_8_planar>
{
    typedef vil_rgba<vxl_uint_8> vil_pixel_t;
    static const unsigned int num_components = 4;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgba_16_planar>
{
    typedef vil_rgba<vxl_uint_16> vil_pixel_t;
    static const unsigned int num_components = 4;
};

template <>
struct VILPixelType<phtr::mem::Storage::rgba_32_planar>
{
    typedef vil_rgba<vxl_uint_32> vil_pixel_t;
    static const unsigned int num_components = 4;
};

#endif // PHTRTEST_VIL_PIXEL_TYPE_H__
