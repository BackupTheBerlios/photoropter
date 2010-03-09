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
            AutoScaler(const IImageTransform& image_transform);

        public:
            /**
            * @brief Try to find the minimal image scale.
            * @details Scaling the image by 1/result should lead to an image without black borders.
            * @param[in] precision The desired reciprocal precision (usually the number of pixels).
            * @param[out] scale The scale
            * @return 'true' if autoscaler was successful, 'false' otherwise.
            */
            bool find_scale(size_t precision, double& scale) const;

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * @brief Perform bisection search.
            * @param[in] precision The precision to be achieved (reciprocal value).
            * @param[in] step      The (remaining) search depth.
            * @param[in,out] val1  The left bracketing value.
            * @param[in,out] val2  The right bracketing value.
            */
            bool bisect(size_t precision, size_t step, double& val1, double& val2) const;

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
            bool find_start_pair(size_t precision, double& val1, double& val2) const;

        private:
            /**
            * @brief Perform iteration step.
            * @param[in] precision The desired reciprocal precision (usually the number of pixels).
            * @param[in] pre_scale Scaling factor from previous iterations.
            */
            double find_scale_step(size_t precision, double pre_scale) const;

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
            double search_horizontal(double aspect_ratio, size_t px_width, double pre_scale) const;

        private:
            /**
            * @brief Perform vertical search.
            * @details The left and right borders of the destination image are
            * 'scanned' fo the minimal scaling factor.
            * @param[in] aspect_ratio The image aspect ratio.
            * @param[in] px_height The image's pixel width to be assumed.
            * @param[in] pre_scale Scaling factor from previous iterations.
            * @return The factor (squared).
            */
            double search_vertical(double aspect_ratio, size_t px_height, double pre_scale) const;

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
            double get_factor(interp_coord_t dest_x, interp_coord_t dest_y, double pre_scale) const;

        private:
            /**
            * @brief Calculate the distance of the point farthest away
            * from the image centre in a given tuple.
            * @param[in] coords The coordinates tuple.
            * @return The distance (squared).
            */
            double maximal_r2(const coord_tuple_T& coords) const;

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

    /**
     * @brief AutoScaler implementation for RGB images.
     */
    typedef AutoScaler<mem::CoordTupleRGB> AutoScalerRGB;

    /**
     * @brief AutoScaler implementation for RGBA images.
     */
    typedef AutoScaler<mem::CoordTupleRGBA> AutoScalerRGBA;

    /**
    * @brief Get an AutoScaler implementation based on the storage type.
    * @details This function determines the storage type at runtime and creates
    * the appropriate auto scaler.
    * @param[in] storage_type The storage type.
    * @param[in] image_transform The image transform object to be used.
    * @return The auto scaler.
    */
    IAutoScaler* get_auto_scaler(mem::Storage::type storage_type, const IImageTransform& image_transform);

} // namespace phtr

#include <photoropter/auto_scaler.tpl.h>

#endif // PHTR_AUTO_SCALER_H__
