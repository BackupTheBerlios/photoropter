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
            * @param precision The desired reciprocal precision (usually the number of pixels).
            * @return The scale.
            */
            virtual double find_scale(size_t precision) const = 0;
    };

    /**
    * @brief Automatic image scaler.
    * @brief The scaling implementation tries to find the 'minimal' scaling factor
    * of the image, so that scaling the image by 1/result should lead to an image
    * without black borders.
    * @note The algorithm is experimental and not strictly guaranteed to converge
    * under all circumstances.
    */
    class AutoScalerImpl : public IAutoScaler
    {

            /* ****************************************
             * public interface
             * **************************************** */

        typedef mem::CoordTupleRGB coord_tuple_t;

        public:
            /**
            * @brief Constructor.
            * @details Copies the geometric transformation queues of a given
            * transformation object.
            * @param image_transform The image transformation object.
            */
            AutoScalerImpl(const IImageTransform& image_transform)
                    : image_transform_(image_transform)
            {
                pixel_queue_ = image_transform_.pixel_queue();
                subpixel_queue_ = image_transform_.subpixel_queue();
            }

        public:
            /**
            * @brief Try to find the minimal image scale.
            * @details Scaling the image by 1/result should lead to an image without black borders.
            * @param precision The desired reciprocal precision (usually the number of pixels).
            * @return The scale.
            */
            double find_scale(size_t precision) const
            {
                const double max_diff = 0.01 / static_cast<double>(precision);
                double diff(2 * max_diff * static_cast<double>(precision));

                double factor(1.0);
                double next_factor(1.0);

                double step_fact = static_cast<double>(precision / 20);

                size_t iter = 0;
                while (iter < precision && diff > max_diff * factor)
                {
                    next_factor = find_scale_step(precision, factor);
                    next_factor = ((step_fact - 1) * factor + next_factor) / static_cast<double>(step_fact);
                    diff = std::fabs(factor - next_factor);

                    factor = next_factor;
                    ++iter;
                }
                std::cerr << iter << std::endl;

                // overshoot slightly to avoid border effects
                return 1.0 / (1.0 / factor + 2.0 / static_cast<double>(precision));
            }

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * @brief Perform iteration step.
            * @param precision The desired reciprocal precision (usually the number of pixels).
            * @param pre_scale Scaling factor from previous iterations.
            */
            double find_scale_step(size_t precision, double pre_scale) const
            {

                size_t px_width = precision;
                size_t px_height = precision;
                double aspect_ratio = 1.5;

                double fact_y = search_horizontal(aspect_ratio, px_width, pre_scale);
                double fact_x = search_vertical(aspect_ratio, px_height, pre_scale);

                double factor = min(fact_x, fact_y);

                return std::sqrt(factor) * pre_scale;

            }

        private:
            /**
            * @brief Perform horizontal search.
            * @details The top and bottom borders of the destination image are
            * 'scanned' fo the minimal scaling factor.
            * @param aspect_ratio The image aspect ratio.
            * @param px_width The image's pixel width to be assumed.
            * @param pre_scale Scaling factor from previous iterations.
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

                    factor_tmp = min(get_factor(cur_dst_x, dst_top, pre_scale),
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
            * @param aspect_ratio The image aspect ratio.
            * @param px_width The image's pixel width to be assumed.
            * @param pre_scale Scaling factor from previous iterations.
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

                    factor_tmp = min(get_factor(dst_left, cur_dst_y, pre_scale),
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
            * @brief Auxiliary function: minimum of two values.
            * @param x1 First value.
            * @param x2 Second value.
            * @return The minimal value.
            */
            double min(double x1, double x2) const
            {
                if (x1 < x2)
                {
                    return x1;
                }
                else
                {
                    return x2;
                }
            }

        private:
            /**
            * @brief Get the 'scaling factor' for a border point.
            * @brief This determines (for a given border point in the destination image) the distance of the
            * corresponding point to the image centre in the source image (squared) and calculates the ratio to
            * the corresponding distance in the destination image.
            * @param dest_x Horizontal coordinate in the destination image.
            * @param dest_y Vertical coordinate in the destination image.
            * @param pre_scale Scaling factor from previous iterations.
            * @return The scaling factor (squared).
            */
            double get_factor(interp_coord_t dest_x, interp_coord_t dest_y, double pre_scale) const
            {
                // distance of the border point to the center (squared)
                interp_coord_t dst_r2 = dest_x * dest_x + dest_y * dest_y;

                mem::CoordTupleMono pixel_coords;
                coord_tuple_t subpixel_coords;

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
            * @param coords The coordinates tuple.
            * @return The distance (squared).
            */
            double maximal_r2(const coord_tuple_t& coords) const
            {
                size_t num_channels = coord_tuple_t::channel_order_t::colour_tuple_t::num_vals;

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
    };

} // namespace phtr

#endif // PHTR_AUTO_SCALER_H__