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

#ifndef PHTR_AUTO_SCALER_H__
#define PHTR_AUTO_SCALER_H__

#include <cmath>
#include <algorithm>

#include <photoropter/pixel_correction_queue.h>
#include <photoropter/subpixel_correction_queue.h>
#include <photoropter/colour_correction_queue.h>
#include <photoropter/image_transform.h>
#include <photoropter/mem/coord_tuple.h>

namespace phtr
{

    /**
    * @brief Automatic image scaler interface.
    * @brief The scaling implementation tries to find the 'minimal' scaling factor
    * of the image, so that scaling the image by 1/result should lead to an image
    * without black borders.
    */
    class IAutoScaler
    {
        public:
            /**
            * @brief (Dummy) destructor.
            */
            virtual ~IAutoScaler() {}

        public:
            /**
            * @brief Try to find the minimal image scale.
            * @details Scaling the image by 1/result should lead to an image without black borders.
            * @param[in] precision The desired reciprocal precision (usually the number of pixels).
            * @param[out] scale The scale
            * @return 'true' if autoscaler was successful, 'false' otherwise.
            */
            virtual bool find_scale(size_t precision, double& scale) const = 0;
    };

    /**
    * @brief Automatic image scaler.
    * @brief The scaling implementation tries to find the 'minimal' scaling factor
    * of the image, so that scaling the image by 1/result should lead to an image
    * without black borders.
    * @note The algorithm is currently to be considered 'experimental' and not
    * strictly guaranteed to converge under all circumstances.
    */
    template <typename coord_tuple_T>
    class AutoScaler : public IAutoScaler
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief Constructor.
            * @details Copies the geometric transformation queues of a given
            * transformation object.
            * @param[in] image_transform The image transformation object.
            */
            AutoScaler(const IImageTransform& image_transform)
                    : image_transform_(image_transform)
            {
                pixel_queue_ = image_transform_.pixel_queue();
                subpixel_queue_ = image_transform_.subpixel_queue();
            }

        public:
            /**
            * @brief Try to find the minimal image scale.
            * @details Scaling the image by 1/result should lead to an image without black borders.
            * @param[in] precision The desired reciprocal precision (usually the number of pixels).
            * @param[out] scale The scale
            * @return 'true' if autoscaler was successful, 'false' otherwise.
            */
            bool find_scale(size_t precision, double& scale) const
            {
                double v1(1.0);
                double v2(1.0);
                bool found_pair = find_start_pair(precision, v1, v2);

                if (!found_pair)
                {
                    return false;
                }

                if (bisect(precision, precision, v1, v2))
                {
                    //std::cerr << "bisect successful: " << v1 << " " << v2 << std::endl;
                    scale = (v1 + v2) / 2.0;
                    return true;
                }
                else
                {
                    return false;
                }

            }

            /* ****************************************
             * internals
             * **************************************** */

    private:
        /**
        * @brief Perform bisection search.
        * @param[in] precision The precision to be achieved (reciprocal value).
        * @param[in] The (remaining) search depth.
        * @param[in,out] val1 The left bracketing value.
        * @param[in,out] val2 The right bracketing value.
        */
        bool bisect(size_t precision, size_t step, double& val1, double& val2) const
        {
            if (!step)
            {
                // search depth exhausted, fail
                return false;
            }

            double mid_val = (val1 + val2) / 2.0;
            double diff = std::fabs(val1 - val2);
            if (static_cast<double>(precision * 10) * diff < std::fabs(mid_val))
            {
                // desired precision achieved, succeed
                return true;
            }

            double scale_step1 = find_scale_step(precision, val1) - 1.0;
            double scale_step2 = find_scale_step(precision, val2) - 1.0;
            double mid_scale_step = find_scale_step(precision, mid_val) - 1.0;
            //std::cerr << step << " " << val1 << " " << scale_step1 + 1.0 << "  " <<
            //    mid_val << " " << mid_scale_step + 1.0 << "  " <<
            //    val2 << " " << scale_step2 + 1.0 << std::endl;

            if (!(scale_step1 * scale_step2 < 0))
            {
                // val1 and val2 not bracketing the value we are looking for, fail
                return false;
            }

            if (scale_step1 * mid_scale_step < 0)
            {
                val2 = mid_val;
            }
            else
            {
                val1 = mid_val;
            }

            // recursion: step one level down
            --step;
            return bisect(precision, step, val1, val2);
        }

    private:
        /**
        * @brief Find the starting pair for the bisection search.
        * @details In this first search, the given start value is examined whether the
        * corresponding scaling factor is >1.0 or <1.0; depending on the result, a
        * quick search for a fitting second value is performed.
        * @param[in] precision The precision to be achieved (reciprocal value).
        * @param[in,out] val1 The left bracketing value. Input is a arbitrary start value,
        * output the found left bracketing value (if any)
        * @param[out] val2 The right bracketing value.
        */
        bool find_start_pair(size_t precision, double& val1, double& val2) const
        {
            double mult(2.0);
            double scale_step = find_scale_step(precision, val1);

            val2 = val1;

            const size_t max_step(10);
            size_t step(0);

            if (scale_step < 1.0)
            {
                while (step < max_step)
                {
                    ++step;
                    val1 /= mult;
                    scale_step = find_scale_step(precision, val1);

                    if (scale_step >= 1.0)
                    {
                        return true;
                    }
                }
            }
            else
            {
                while (step < max_step)
                {
                    ++step;
                    val2 *= mult;
                    scale_step = find_scale_step(precision, val2);

                    if (scale_step < 1.0)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        private:
            /**
            * @brief Perform iteration step.
            * @param[in] precision The desired reciprocal precision (usually the number of pixels).
            * @param[in] pre_scale Scaling factor from previous iterations.
            */
            double find_scale_step(size_t precision, double pre_scale) const
            {

                size_t px_width = precision;
                size_t px_height = precision;
                double aspect_ratio = 1.5;

                double fact_y = search_horizontal(aspect_ratio, px_width, pre_scale);
                double fact_x = search_vertical(aspect_ratio, px_height, pre_scale);

                double factor = std::min(fact_x, fact_y);

                return std::sqrt(factor);

            }

        private:
            /**
            * @brief Perform horizontal search.
            * @details The top and bottom borders of the destination image are
            * 'scanned' fo the minimal scaling factor.
            * @param[in] aspect_ratio The image aspect ratio.
            * @param[in] px_width The image's pixel width to be assumed.
            * @param[in] pre_scale Scaling factor from previous iterations.
            * @return The factor (squared).
            */
            double search_horizontal(double aspect_ratio, size_t px_width, double pre_scale) const
            {
                interp_coord_t dst_top = -1.0;
                interp_coord_t dst_bottom = 1.0;

                interp_coord_t scale_x = 2.0 * aspect_ratio / static_cast<interp_coord_t>(px_width - 1);

                double factor_tmp(1.0);
                double factor(1.0);
                bool first(true);

                for (size_t i = 0; i < px_width; ++i)
                {
                    // current pixel position
                    interp_coord_t cur_pixel_x(static_cast<interp_coord_t>(i));
                    interp_coord_t cur_dst_x = cur_pixel_x * scale_x - aspect_ratio;

                    factor_tmp = std::min(get_factor(cur_dst_x, dst_top, pre_scale),
                                     get_factor(cur_dst_x, dst_bottom, pre_scale));
                    if (first)
                    {
                        first = false;
                        factor = factor_tmp;
                    }
                    else if (factor_tmp < factor)
                    {
                        factor = factor_tmp;
                    }

                }

                return factor;
            }

        private:
            /**
            * @brief Perform vertical search.
            * @details The left and right borders of the destination image are
            * 'scanned' fo the minimal scaling factor.
            * @param[in] aspect_ratio The image aspect ratio.
            * @param[in] px_width The image's pixel width to be assumed.
            * @param[in] pre_scale Scaling factor from previous iterations.
            * @return The factor (squared).
            */
            double search_vertical(double aspect_ratio, size_t px_height, double pre_scale) const
            {
                interp_coord_t dst_left = -aspect_ratio;
                interp_coord_t dst_right = aspect_ratio;

                interp_coord_t scale_y = 2.0 / static_cast<interp_coord_t>(px_height - 1);

                double factor_tmp(1.0);
                double factor(1.0);
                bool first(true);

                for (size_t i = 0; i < px_height; ++i)
                {
                    // current pixel position
                    interp_coord_t cur_pixel_y(static_cast<interp_coord_t>(i));
                    interp_coord_t cur_dst_y = cur_pixel_y * scale_y - 1.0;

                    factor_tmp = std::min(get_factor(dst_left, cur_dst_y, pre_scale),
                                     get_factor(dst_right, cur_dst_y, pre_scale));
                    if (first)
                    {
                        first = false;
                        factor = factor_tmp;
                    }
                    else if (factor_tmp < factor)
                    {
                        factor = factor_tmp;
                    }

                }

                return factor;
            }

        private:
            /**
            * @brief Get the 'scaling factor' for a border point.
            * @brief This determines (for a given border point in the destination image) the distance of the
            * corresponding point to the image centre in the source image (squared) and calculates the ratio to
            * the corresponding distance in the destination image.
            * @param[in] dest_x Horizontal coordinate in the destination image.
            * @param[in] dest_y Vertical coordinate in the destination image.
            * @param[in] pre_scale Scaling factor from previous iterations.
            * @return The scaling factor (squared).
            */
            double get_factor(interp_coord_t dest_x, interp_coord_t dest_y, double pre_scale) const
            {
                // distance of the border point to the center (squared)
                interp_coord_t dst_r2 = dest_x * dest_x + dest_y * dest_y;

                mem::CoordTupleMono pixel_coords;
                coord_tuple_T subpixel_coords;

                // apply coordinate transformations
                pixel_queue_.get_src_coords(dest_x * pre_scale, dest_y * pre_scale, pixel_coords);
                subpixel_queue_.get_src_coords(pixel_coords, subpixel_coords);

                // determine minimal coordinates in source image (i.e., the ones closest to the image center)
                // and return ratio
                return dst_r2 / maximal_r2(subpixel_coords);
            }

        private:
            /**
            * @brief Calculate the distance of the point farthest away
            * from the image centre in a given tuple.
            * @param[in] coords The coordinates tuple.
            * @return The distance (squared).
            */
            double maximal_r2(const coord_tuple_T& coords) const
            {
                size_t num_channels = coord_tuple_T::channel_order_t::colour_tuple_t::num_vals;

                interp_coord_t r2(1.0);
                bool first(true);

                for (size_t i = 0; i < num_channels; ++i)
                {
                    interp_coord_t r2_tmp = coords.x[i] * coords.x[i] + coords.y[i] * coords.y[i];

                    if (first)
                    {
                        r2 = r2_tmp;
                        first = false;
                    }
                    else if (r2 < r2_tmp)
                    {
                        r2 = r2_tmp;
                    }
                }

                return r2;
            }

        private:
            /**
            * @brief Internal reference to the image transform object.
            */
            const IImageTransform& image_transform_;

        private:
            /**
            * @brief The internal queue of geometrical correction models to be applied.
            */
            PixelCorrectionQueue pixel_queue_;

        private:
            /**
            * @brief The internal queue of geometrical correction models to be applied.
            */
            SubpixelCorrectionQueue subpixel_queue_;

    }; // template class AutoScaler<>

    typedef AutoScaler<mem::CoordTupleRGB> AutoScalerRGB;
    typedef AutoScaler<mem::CoordTupleRGBA> AutoScalerRGBA;

    /**
    * @brief Get an AutoScaler implementation based on the storage type.
    * @details This function determines the storage type at runtime and creates
    * the appropriate auto scaler.
    * @param[in] storage_type The storage type.
    * @param[in] image_transform The image transform object to be used.
    * @return The auto scaler.
    */
    inline IAutoScaler* get_auto_scaler(mem::Storage::type storage_type, const IImageTransform& image_transform)
    {
        switch (storage_type)
        {
        case mem::Storage::rgb_8_inter:
        default:
            return new AutoScalerRGB(image_transform);
            break;

        case mem::Storage::rgb_16_inter:
            return new AutoScalerRGB(image_transform);
            break;

        case mem::Storage::rgb_32_inter:
            return new AutoScalerRGB(image_transform);
            break;

        case mem::Storage::rgba_8_inter:
            return new AutoScalerRGBA(image_transform);
            break;

        case mem::Storage::rgba_16_inter:
            return new AutoScalerRGBA(image_transform);
            break;

        case mem::Storage::rgba_32_inter:
            return new AutoScalerRGBA(image_transform);
            break;
        }
    }

} // namespace phtr

#endif // PHTR_AUTO_SCALER_H__
