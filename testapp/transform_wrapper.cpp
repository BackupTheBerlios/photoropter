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

#include <vil/vil_load.h>

#include "transform_wrapper.h"

TransformWrapperBase*
TransformWrapperBase::
get_instance(const Settings& settings)
{
    using phtr::mem::Storage;

    Storage::type storage_type = get_storage_type(settings.inp_file);

    if (storage_type == Storage::rgb_8_inter)
    {
        return new TransformWrapper<Storage::rgb_8_inter>(settings);
    }
    else if (storage_type == Storage::rgb_16_inter)
    {
        return new TransformWrapper<Storage::rgb_16_inter>(settings);
    }
    else if (storage_type == Storage::rgb_32_inter)
    {
        return new TransformWrapper<Storage::rgb_32_inter>(settings);
    }
    else if (storage_type == Storage::rgba_8_inter)
    {
        return new TransformWrapper<Storage::rgba_8_inter>(settings);
    }
    else if (storage_type == Storage::rgba_16_inter)
    {
        return new TransformWrapper<Storage::rgba_16_inter>(settings);
    }
    else if (storage_type == Storage::rgba_32_inter)
    {
        return new TransformWrapper<Storage::rgba_32_inter>(settings);
    }

    return 0;
}

phtr::mem::Storage::type
TransformWrapperBase::
get_storage_type(const std::string inp_file)
{
    using phtr::mem::Storage;
    Storage::type phtr_storage = Storage::unknown;

    vil_image_resource_sptr img_res = vil_load_image_resource(inp_file.c_str());
    vil_pixel_format vil_img_format = img_res->pixel_format();

    unsigned int num_components = img_res->nplanes();

    if (num_components == 3)
    {
        if (vil_img_format == VIL_PIXEL_FORMAT_BYTE)
        {
            phtr_storage = Storage::rgb_8_inter;
        }
        else if (vil_img_format == VIL_PIXEL_FORMAT_UINT_16)
        {
            phtr_storage = Storage::rgb_16_inter;
        }
        else if (vil_img_format == VIL_PIXEL_FORMAT_UINT_32)
        {
            phtr_storage = Storage::rgb_32_inter;
        }
    }
    else if (num_components == 4)
    {
        if (vil_img_format == VIL_PIXEL_FORMAT_BYTE)
        {
            phtr_storage = Storage::rgba_8_inter;
        }
        else if (vil_img_format == VIL_PIXEL_FORMAT_UINT_16)
        {
            phtr_storage = Storage::rgba_16_inter;
        }
        else if (vil_img_format == VIL_PIXEL_FORMAT_UINT_32)
        {
            phtr_storage = Storage::rgba_32_inter;
        }
    }

    return phtr_storage;
}
