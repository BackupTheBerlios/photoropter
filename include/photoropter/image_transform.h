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

#ifndef __PHTR_IMAGE_TRANSFORM_H__
#define __PHTR_IMAGE_TRANSFORM_H__

#include <vector>

#include <photoropter/geom_correction_queue.h>
#include <photoropter/colour_correction_queue.h>
#include <photoropter/gamma_func.h>

namespace phtr
{

    /**
    * @brief Image transformation class template.
    * @details Inside this class, the actual image transformation is performed.
    * @param interpolator_t The interpolator class to be used.
    * @param image_view_w_t The writing image view class to be used.
    * @param oversampling   The (over-)sampling factor.
    */
    template < typename interpolator_t, typename image_view_w_t, unsigned int oversampling = 1 >
    class ImageTransform
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief The type of the input image view.
            */
            typedef typename interpolator_t::image_view_t image_view_t;

        public:
            /**
            * @brief The channel storage type.
            */
            typedef typename image_view_w_t::storage_info_t::channel_storage_t channel_storage_t;

        public:
            /**
            * @brief Constructor.
            * @param[in] image_view_r Input image view.
            * @param[in] image_view_w Output image view.
            */
            ImageTransform(const typename ImageTransform::image_view_t& image_view_r, image_view_w_t& image_view_w);

        public:
            /**
            * @brief Transform the image.
            * @details The image data is read from the input image view and
            * written to the output view, while applying selected transformations.
            */
            void do_transform();

        public:
            /**
            * @brief Access the geometry correction queue.
            * @return Reference to the queue object.
            */
            GeomCorrectionQueue& geom_queue();

        public:
            /**
            * @brief Access the colour correction queue.
            * @return Reference to the queue object.
            */
            ColourCorrectionQueue& colour_queue();

        public:
            /**
            * @brief Set the %gamma correction.
            * @details This function fills the internal %gamma correction tables
            * using the given function.
            * @param[in] gam_func The %gamma function to be used.
            */
            void set_gamma(const gamma::IGammaFunc& gam_func);

        public:
            /**
            * @brief Set the %gamma correction.
            * @details This function fills the internal %gamma correction tables
            * using the given function.
            * @param[in] gam_func The %gamma function to be used.
            * @param[in] inv_gam_func The %gamma function to be used for inverse correction.
            */
            void set_gamma(const gamma::IGammaFunc& gam_func,
                           const gamma::IGammaFunc& inv_gam_func);

        public:
            /**
            * @brief Set the precision of the %gamma interpolation.
            * @details The default is to use 1024 points for interpolation.
            * Changing this will not have any effect until the next call to @ref set_gamma().
            * @param[in] num The number of points-
            */
            void set_gamma_precision(unsigned int num);

        public:
            /**
            * @brief Enable/disable %gamma handling.
            * @details If %gamma is disabled completely, things get a little bit
            * faster; however, use it only on linear input or if performing no
            * colour corrections, or you will get wrong output.
            * @param[in] do_enable If 'true', enable %gamma correction, disable otherwise.
            */
            void enable_gamma(bool do_enable);

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * @brief Apply channel clipping.
            * @param[in,out] val_r 'red' channel value.
            * @param[in,out] val_g 'green' channel value.
            * @param[in,out] val_b 'blue' channel value.
            */
            inline void clip_vals(interp_channel_t& val_r,
                                  interp_channel_t& val_g,
                                  interp_channel_t& val_b);

        private:
            /**
            * @brief Normalise a channel value to [0:1.0]
            * @param[in] value The unnormalised value.
            * @return The normalised value.
            */
            inline interp_channel_t normalise(interp_channel_t value);

        private:
            /**
            * @brief Scale a normalised value to the full channel range.
            * @param[in] value The normalised value.
            * @return The scaled value.
            */
            inline interp_channel_t unnormalise(interp_channel_t value);

        private:
            /**
            * @brief Apply %gamma transformation.
            * @details The actual transformation value is determined using a fast lookup
            * table interpolation.
            * @param[in] value The input value.
            * @return The transformed value.
            */
            inline float gamma(float value);

        private:
            /**
            * @brief Apply inverse %gamma transformation.
            * @details The actual transformation value is determined using a fast lookup
            * table interpolation.
            * @param[in] value The input value.
            * @return The transformed value.
            */
            inline float inv_gamma(float value);

        private:
            /**
            * @brief Internal interpolator object.
            * @details The interpolator uses the input view given in the constructor.
            */
            interpolator_t interpolator_;

        private:
            /**
            * @brief Internal output image view object.
            */
            image_view_w_t& image_view_w_;

        private:
            /**
            * @brief The internal queue of geometrical correction models to be applied.
            */
            GeomCorrectionQueue geom_queue_;

        private:
            /**
            * @brief The internal queue of colour correction models to be applied.
            */
            ColourCorrectionQueue colour_queue_;

        private:
            /**
            * @brief Width of the output image.
            */
            coord_t outp_img_width_;

        private:
            /**
            * @brief Height of the output image.
            */
            coord_t outp_img_height_;

        private:
            /**
            * @brief Internal object holding information on storage details
            * (needed for e.g. the maximal channel values).
            */
            typename image_view_w_t::storage_info_t storage_info_;

        private:
            /**
            * @brief The minimal channel value (set correctly before the transformation)
            */
            interp_channel_t min_chan_val_;

        private:
            /**
            * @brief The maximal channel value (set correctly before the transformation)
            */
            interp_channel_t max_chan_val_;

        private:
            /**
            * @brief Flag controlling %gamma correction.
            */
            bool do_gamma_;

        private:
            /**
            * @brief Flag controlling %gamma correction.
            */
            bool do_inv_gamma_;

        private:
            /**
            * @brief Number of points in the %gamma lookup tables after next call
            * to @ref set_gamma().
            * @details Actually, the number of points in the lookup table will be
            * gam_point_new_max_ + 1.
            */
            int gam_point_new_max_;

        private:
            /**
            * @brief Number of points in the %gamma lookup tables.
            * @details Actually, the number of points in the lookup table is
            * gam_point_cur_max_ + 1.
            */
            int gam_point_cur_max_;

        private:
            /**
            * @brief Lookup table for %gamma correction (interpolation parameter 'a').
            */
            std::vector<float> gam_val_a_;

        private:
            /**
            * @brief Lookup table for %gamma correction (interpolation parameter 'b').
            */
            std::vector<float> gam_val_b_;

        private:
            /**
            * @brief Lookup table for inverse %gamma correction (interpolation parameter 'a').
            */
            std::vector<float> inv_gam_val_a_;

        private:
            /**
            * @brief Lookup table for inverse %gamma correction (interpolation parameter 'b').
            */
            std::vector<float> inv_gam_val_b_;

    }; // class ImageTransform

} // namespace phtr

#include <photoropter/image_transform.tpl.h>

#endif // __PHTR_IMAGE_TRANSFORM_H__
