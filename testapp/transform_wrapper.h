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

#ifndef PHTRTEST_TRANSFORM_WRAPPER_H__
#define PHTRTEST_TRANSFORM_WRAPPER_H__

#include <string>
#include <memory>

#include "vil_pixel_type.h"
#include "settings.h"

#include <photoropter/mem/storage_type.h>
#include <photoropter/image_buffer.h>
#include <photoropter/mem_image_view_r.h>
#include <photoropter/mem_image_view_w.h>
#include <photoropter/interpolator_nn.h>
#include <photoropter/interpolator_bilinear.h>
#include <photoropter/interpolator_lanczos.h>
#include <photoropter/image_transform.h>

#include <vil/vil_convert.h>
#include <vil/vil_load.h>
#include <vil/vil_save.h>

class TransformWrapperBase
{

    public:
        /**
         * @brief Initialise and return a transformation object compatible with the given settings.
         */
        static TransformWrapperBase* get_instance(const Settings& settings);

        /**
         * @brief Perform the transformation.
         */
        virtual void do_transform() = 0;

        /**
         * @brief Save the transformation result.
         */
        virtual void save() = 0;

    private:
        /**
            * @brief Determine a compatible storage type (i.e., check the bit depth of the given file)
            */
        static phtr::mem::Storage::type get_storage_type(const std::string inp_file);

};

template <phtr::mem::Storage::type storage_T>
class TransformWrapper : public TransformWrapperBase
{
    public:
        typedef phtr::ImageBuffer<storage_T> buffer_t;
        typedef phtr::MemImageViewR<storage_T> view_r_t;
        typedef phtr::MemImageViewW<storage_T> view_w_t;
        typedef typename view_w_t::iter_t iter_t;

        typedef phtr::InterpolatorNN<view_r_t> interp_nn_t;
        typedef phtr::InterpolatorBilinear<view_r_t> interp_bilinear_t;
        typedef phtr::InterpolatorLanczos<view_r_t> interp_lanczos_t;

        typedef phtr::ImageTransform<interp_nn_t, view_w_t> transform_nn_t;
        typedef phtr::ImageTransform<interp_bilinear_t, view_w_t> transform_bilinear_t;
        typedef phtr::ImageTransform<interp_lanczos_t, view_w_t> transform_lanczos_t;

        typedef typename VILPixelType<storage_T>::vil_pixel_t vil_pixel_t;

    public:
        TransformWrapper(const Settings& settings);
        void do_transform();
        void save();

    private:
        void load();
        void init_transform();
        void setup_transform();
        void set_gainfunc();
        void add_models();

    private:
        static const unsigned int num_components_ = VILPixelType<storage_T>::num_components;
        size_t img_width_;
        size_t img_height_;
        size_t dst_width_;
        size_t dst_height_;

        const Settings settings_;

        std::auto_ptr<buffer_t> input_buffer_;
        std::auto_ptr<buffer_t> output_buffer_;

        std::auto_ptr<view_r_t> input_view_;
        std::auto_ptr<view_w_t> output_view_;

        std::auto_ptr<phtr::IImageTransform> image_transform_;
};

#include "transform_wrapper.tpl.h"

#endif // PHTRTEST_TRANSFORM_WRAPPER_H__
