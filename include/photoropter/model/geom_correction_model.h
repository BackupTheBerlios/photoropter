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

#ifndef PHTR_GEOM_CORRECTION_MODEL_H__
#define PHTR_GEOM_CORRECTION_MODEL_H__

#include <photoropter/types.h>
#include <photoropter/mem/coord_tuple.h>
#include <photoropter/model/correction_model_base.h>

namespace phtr
{

    namespace model
    {

        /**
        * @brief Interface base class for geometrical lens correction models.
        * @details The corrections models are implemented using a 'functionid' pattern.
        */
        class IGeomCorrectionModel
        {

            public:
                /**
                 * @ brief (Dummy) Destructor.
                 */
                virtual ~IGeomCorrectionModel() {};

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                virtual void get_src_coords(mem::CoordTupleRGB& coords) const = 0;

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                virtual void get_src_coords(mem::CoordTupleRGBA& coords) const = 0;

            public:
                /**
                * @brief Create a clone of the correction %model functionoid.
                * @return The clone.
                */
                virtual IGeomCorrectionModel* clone() const = 0;

        }; // class IGeomCorrectionModel

        /**
        * @brief The PTLens geometric correction %model.
        * @details The PTLens correction %model implements the following formula: @f[
        * r_{src} = (a r_{dst}^3 + b r_{dst}^2 + c r_{dst} + d)  r_{dst}
        * @f]
        * Usually, 'd' is either left at a fixed value of 1, or calculated to that a+b+c+d=1.
        * Additionally, coordinates describing a shift of the centre can be used. Hugin and
        * PanoTools usually call these 'd' and 'e', thus creating a bit of a confusion
        * concerning the 'd' parameter in the formula above. Because of that, Photoropter
        * uses the format (x0, y0) to designate the centre shift.
        * @note The PTLens geometric %model is used by the PanoTools components 'fulla' and
        * 'tca_correct' to correct for transverse chromatic aberration (TCA) as well, since
        * this is approach is more general than a simple linear %model. The Photoropter
        * implementation fully supports this usage as well: one just uses two instances of
        * the %model, one for TCA and one for distortion correction. Use
        * @ref set_model_params_single() to set the coefficents for red and blue shift
        * in the TCA %model.
        */
        class PTLensGeomModel : public IGeomCorrectionModel, private CorrectionModelBase
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
                PTLensGeomModel(double param_aspect, double input_aspect,
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
                explicit PTLensGeomModel(double input_aspect);

            public:
                /**
                * @brief Set the %model parameters (single channel).
                * @note This function is mainly useful for TCA corrections.
                * @param[in] chan_idx The channel index.
                * The correct way to determine this value is via the
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[in] a        The 'a' parameter.
                * @param[in] b        The 'b' parameter.
                * @param[in] c        The 'c' parameter.
                * @param[in] d        The 'd' parameter.
                */
                void set_model_params_single(size_t chan_idx, double a, double b, double c, double d);

            public:
                /**
                * @brief Set the %model parameters (all channels).
                * @param[in] a The 'a' parameter.
                * @param[in] b The 'b' parameter.
                * @param[in] c The 'c' parameter.
                * @param[in] d The 'd' parameter.
                */
                void set_model_params(double a, double b, double c, double d);

            public:
                /**
                * @brief Set the %model parameters (single channel).
                * @note This function is mainly useful for TCA corrections.
                * fulla/tca_correct always calculate TCA with all four parameters, so this variant
                * exists more or less for the sake of completeness.
                * @details The 'd' parameter is automatically calculated so that a+b+c+d=1.
                * This way, the vertical viewing angle is preserved; this will result in distortion in
                * the image centre, but in a lower overall distortion of the image. This is also
                * what both Hugin and PTLens are usually doing.
                * @param[in] chan_idx The channel index.
                * The correct way to determine this value is via the
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[in] a        The 'a' parameter.
                * @param[in] b        The 'b' parameter.
                * @param[in] c        The 'c' parameter.
                */
                void set_model_params_single(size_t chan_idx, double a, double b, double c);

            public:
                /**
                * @brief Set the %model parameters (all channels).
                * @details The 'd' parameter is automatically calculated so that a+b+c+d=1.
                * This way, the vertical viewing angle is preserved; this will result in distortion in
                * the image centre, but in a lower overall distortion of the image. This is also
                * what both Hugin and PTLens are usually doing.
                * @param[in] a The 'a' parameter.
                * @param[in] b The 'b' parameter.
                * @param[in] c The 'c' parameter.
                */
                void set_model_params(double a, double b, double c);

            public:
                /**
                * @brief Get the %model parameters.
                * @param[in]  chan_idx The channel index.
                * The correct way to determine this value is via the
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[out] a        The 'a' parameter.
                * @param[out] b        The 'b' parameter.
                * @param[out] c        The 'c' parameter.
                * @param[out] d        The 'd' parameter.
                */
                void get_model_params(size_t chan_idx, double& a, double& b, double& c, double& d) const;

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
                IGeomCorrectionModel* clone() const;

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
                * @brief The parameter 'a'.
                */
                double a_[mem::PHTR_MAX_CHANNELS];

            private:
                /**
                * @brief The parameter 'b'.
                */
                double b_[mem::PHTR_MAX_CHANNELS];

            private:
                /**
                * @brief The parameter 'c'.
                */
                double c_[mem::PHTR_MAX_CHANNELS];

            private:
                /**
                * @brief The parameter 'd'.
                */
                double d_[mem::PHTR_MAX_CHANNELS];

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

        }; // class PTLensGeomModel

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
        class ScalerGeomModel : public IGeomCorrectionModel, private CorrectionModelBase
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
                ScalerGeomModel(double param_aspect, double input_aspect,
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
                explicit ScalerGeomModel(double input_aspect);

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
                IGeomCorrectionModel* clone() const;

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

        }; // class ScalerGeomModel

    } // namespace phtr::model

} // namespace phtr

#endif // PHTR_GEOM_CORRECTION_MODEL_H__
