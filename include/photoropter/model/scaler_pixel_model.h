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

#ifndef PHTR_SCALER_PIXEL_MODEL_H__
#define PHTR_SCALER_PIXEL_MODEL_H__

#include <photoropter/model/subpixel_correction_model.h>
#include <photoropter/model/pixel_correction_model.h>
#include <photoropter/model/correction_model_base.h>

namespace phtr
{

    namespace model
    {

        /**
        * @brief A simple scaling geometric correction %model.
        * @details The scaler %model implements the following formula: @f[
        * r_{src} = \frac{r_{dst}}{k}
        * @f]
        * @note Keep in mind that Photoropter defines image transformations in the
        * "backward" direction, i.e. values k>1 lead to an enlargement of the image.
        * @note This class can also be used as a simple linear TCA correction %model.
        * For that purpose, one uses an additional instance of the %model for TCA. Use
        * @ref set_model_param_single() to set the coefficents for red and blue shift
        * in the TCA %model.
        */
        class ScalerPixelModel
                    : private CorrectionModelBase,
                    public ISubpixelCorrectionModel,
                    public IPixelCorrectionModel
        {

                /* ****************************************
                * public interface
                * **************************************** */

            public:
                /**
                * @brief Constructor.
                * @details In this variant, the complete information describing both the coordinate system used
                * when determining the %model parameters and the coordinate system of the input image are used.
                * @param[in] param_aspect The aspect ratio that was used when determining the %model parameters.
                * @param[in] input_aspect The aspect ratio of the input image.
                * @param[in] param_crop The crop factor that was used when determining the %model parameters.
                * @param[in] input_crop The crop factor of the input image.
                */
                ScalerPixelModel(double param_aspect, double input_aspect,
                                 double param_crop, double input_crop);

            public:
                /**
                * @brief Constructor.
                * @details When construction the %model using this constructor, the following things are
                * assumed:
                * <ol><li>The parameters were determined on an image of the same aspect ratio in landscape
                * orientation (i.e., if the input aspect is <1.0, then 1/input_aspect is assumed for the
                * parameter aspect ratio.</li>
                * <li>The image and the parameter set use the same crop factor (i.e., both factors are
                * set to 1.0).</li></ol>
                * @param[in] input_aspect The aspect ratio of the input image.
                */
                explicit ScalerPixelModel(double input_aspect);

            public:
                /**
                * @brief Set the %model parameter (single channel).
                * @note This function is mainly useful for TCA corrections.
                * @param[in] chan_idx The channel index.
                * The correct way to determine this value is via the
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[in] k The scaling parameter.
                */
                void set_model_param_single(size_t chan_idx, double k);

            public:
                /**
                * @brief Set the %model parameter (all channels).
                * @param[in] k The scaling parameter.
                */
                void set_model_param(double k);

            public:
                /**
                * @brief Get the %model parameter.
                * @param[in]  chan_idx The channel index.
                * The correct way to determine this value is via the
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[out] k The scaling parameter.
                */
                void get_model_param(size_t chan_idx, double& k) const;

            public:
                /**
                * @brief Set the centre shift (all channels).
                * @note Both x0 and y0 are not considered 'lens parameters' but rather camera/sensor
                * parameters. They are therefore @em not transformed in any way, but always interpreted
                * in the normalised Photoropter coordinate system.
                * @param[in]  chan_idx The channel index.
                * The correct way to determine this value is via the
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[in] x0 The 'x0' parameter (horizontal centre shift).
                * @param[in] y0 The 'y0' parameter (vertical centre shift).
                */
                void set_centre_shift_single(size_t chan_idx, interp_coord_t x0, interp_coord_t y0);

            public:
                /**
                * @brief Set the centre shift (all channels).
                * @note Both x0 and y0 are not considered 'lens parameters' but rather camera/sensor
                * parameters. They are therefore @em not transformed in any way, but always interpreted
                * in the normalised Photoropter coordinate system.
                * @param[in] x0 The 'x0' parameter (horizontal centre shift).
                * @param[in] y0 The 'y0' parameter (vertical centre shift).
                */
                void set_centre_shift(interp_coord_t x0, interp_coord_t y0);

            public:
                /**
                * @brief Get the centre shift.
                * @note Both x0 and y0 are not considered 'lens parameters' but rather camera/sensor
                * parameters. They are therefore @em not transformed in any way, but always interpreted
                * in the normalised Photoropter coordinate system.
                * @param[in]  chan_idx The channel index.
                * The correct way to determine this value is via the
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[out] x0       The 'x0' parameter (horizontal centre shift).
                * @param[out] y0       The 'y0' parameter (vertical centre shift).
                */
                void get_centre_shift(size_t chan_idx, interp_coord_t& x0, interp_coord_t& y0) const;

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                void get_src_coords(mem::CoordTupleMono& coords) const;

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                void get_src_coords(mem::CoordTupleRGB& coords) const;

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                void get_src_coords(mem::CoordTupleRGBA& coords) const;

            public:
                /**
                * @brief Create a clone of the correction %model functionoid.
                * @return The clone.
                */
                ScalerPixelModel* clone() const;

                /* ****************************************
                * internals
                * **************************************** */

            private:
                /**
                * @brief Get the corrected source image coordinates for the current position (implementation).
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                template <typename coord_tuple_T>
                inline void get_src_coords_impl(coord_tuple_T& coords) const;

            private:
                /**
                * @brief The parameter 'k'.
                */
                double k_[mem::PHTR_MAX_CHANNELS];

            private:
                /**
                * @brief The parameter 'x0'.
                */
                double x0_[mem::PHTR_MAX_CHANNELS];

            private:
                /**
                * @brief The parameter 'y0'.
                */
                double y0_[mem::PHTR_MAX_CHANNELS];

        }; // class ScalerPixelModel

    } // namespace phtr::model

} // namespace phtr

#endif // PHTR_SCALER_PIXEL_MODEL_H__
