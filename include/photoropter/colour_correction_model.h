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

#ifndef __PHTR_COLOUR_CORRECTION_MODEL_H__
#define __PHTR_COLOUR_CORRECTION_MODEL_H__

#include <photoropter/types.h>
#include <photoropter/coord_tuple.h>
#include <photoropter/colour_tuple.h>
#include <photoropter/channel_type.h>
#include <photoropter/correction_model_base.h>

namespace phtr
{

    namespace model
    {

        /**
        * @brief Interface base class for colour correction models.
        * @details The corrections models are implemented using a 'functionid' pattern.
        */
        class IColourCorrectionModel
        {

            public:
                /**
                * @brief Get the correction factors for a given position.
                * @param[in] src_x_r The corresponding x coordinate for the 'red' channel
                *                    in the source image.
                * @param[in] src_y_r The corresponding y coordinate for the 'red' channel
                *                    in the source image.
                * @param[in] src_x_g The corresponding x coordinate for the 'green' channel
                *                    in the source image.
                * @param[in] src_y_g The corresponding y coordinate for the 'green' channel
                *                    in the source image.
                * @param[in] src_x_b The corresponding x coordinate for the 'blue' channel
                *                    in the source image.
                * @param[in] src_y_b The corresponding y coordinate for the 'blue' channel
                *                    in the source image.
                * @param[out] fact_r The correction factor for the 'red' channel.
                * @param[out] fact_g The correction factor for the 'green' channel.
                * @param[out] fact_b The correction factor for the 'blue' channel.
                */
                virtual void get_correction_factors(interp_coord_t src_x_r, interp_coord_t src_y_r,
                                                    interp_coord_t src_x_g, interp_coord_t src_y_g,
                                                    interp_coord_t src_x_b, interp_coord_t src_y_b,
                                                    double& fact_r, double& fact_g, double& fact_b) const = 0;

            public:
                /**
                * @brief Get the correction factors for a given position.
                * @param[in] coords The coordinates in the source image.
                * @param[out] factors The correction factors.
                */
                virtual void get_correction_factors(const mem::CoordTupleRGB& coords,
                                                    mem::ColourTupleRGB& factors) const = 0;

            public:
                /**
                * @brief Create a clone of the correction model functionoid.
                * @return The clone.
                */
                virtual IColourCorrectionModel* clone() const = 0;

        }; // class IColourCorrectionModel

        /**
        * @brief Colour correction model implementing vignetting correction.
        * @details This model compensates for vignetting using the following
        * formula <a href="http://hugin.sourceforge.net/tech/">proposed</a> by
        * Pablo d'Angelo: @f[
        * C_{src} = \frac{C_{dst}}{ar^6+br^4+cr^2+1}
        * @f]
        * This model is also used by Hugin, but with slightly different coordinates.
        * @attention This model is incompatible with vignetting parameters produced by Hugin,
        * since Hugin uses different coordinate systems for geometric correction and for
        * vignetting. Please use @ref HuginVignettingModel to deal with parameters
        * produced by Hugin.
        */
        class VignettingColourModel : public IColourCorrectionModel, protected CorrectionModelBase
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief Constructor.
                * @details In this variant, the complete information describing both the coordinate system used
                * when determining the model parameters and the coordinate system of the input image are used.
                * @param[in] param_aspect The aspect ratio that was used when determining the model parameters.
                * @param[in] input_aspect The aspect ratio of the input image.
                * @param[in] param_crop The crop factor that was used when determining the model parameters.
                * @param[in] input_crop The crop factor of the input image.
                */
                VignettingColourModel(double param_aspect, double input_aspect,
                                      double param_crop, double input_crop);

                /**
                * @brief Constructor.
                * @details When construction the model using this constructor, the following things are
                * assumed:
                * <ol><li>The parameters were determined on an image of the same aspect ratio in landscape
                * orientation (i.e., if the input aspect is <1.0, then 1/input_aspect is assumed for the
                * parameter aspect ratio.</li>
                * <li>The image and the parameter set use the same crop factor (i.e., both factors are
                * set to 1.0).</li></ol>
                * @param[in] input_aspect The aspect ratio of the input image.
                */
                explicit VignettingColourModel(double input_aspect);

            public:
                /**
                * @brief Set the model parameters.
                * @param[in] a The 'a' parameter.
                * @param[in] b The 'b' parameter.
                * @param[in] c The 'c' parameter.
                */
                void set_model_params(double a, double b, double c);

            public:
                /**
                * @brief Get the current model parameters.
                * @param[out] a The 'a' parameter.
                * @param[out] b The 'b' parameter.
                * @param[out] c The 'c' parameter.
                */
                void get_model_params(double& a, double& b, double& c) const;

            public:
                /**
                * @brief Set the centre shift.
                * @param[in] x0 The 'x0' parameter (horizontal centre shift).
                * @param[in] y0 The 'y0' parameter (vertical centre shift).
                * @note Both x0 and y0 are not considered 'lens parameters' but rather camera/sensor
                * parameters. They are therefore @em not transformed in any way, but always interpreted
                * in the normalised Photoropter coordinate system.
                */
                void set_centre_shift(interp_coord_t x0, interp_coord_t y0);

            public:
                /**
                * @brief Get the centre shift.
                * @param[out] x0 The 'x0' parameter (horizontal centre shift).
                * @param[out] y0 The 'y0' parameter (vertical centre shift).
                * @note Both x0 and y0 are not considered 'lens parameters' but rather camera/sensor
                * parameters. They are therefore @em not transformed in any way, but always interpreted
                * in the normalised Photoropter coordinate system.
                */
                void get_centre_shift(interp_coord_t& x0, interp_coord_t& y0) const;

            public:
                /**
                * @brief Get the correction factors for the given position.
                * @param[in] src_x_r The corresponding x coordinate for the 'red' channel
                *                    in the source image.
                * @param[in] src_y_r The corresponding y coordinate for the 'red' channel
                *                    in the source image.
                * @param[in] src_x_g The corresponding x coordinate for the 'green' channel
                *                    in the source image.
                * @param[in] src_y_g The corresponding y coordinate for the 'green' channel
                *                    in the source image.
                * @param[in] src_x_b The corresponding x coordinate for the 'blue' channel
                *                    in the source image.
                * @param[in] src_y_b The corresponding y coordinate for the 'blue' channel
                *                    in the source image.
                * @param[out] fact_r The correction factor for the 'red' channel.
                * @param[out] fact_g The correction factor for the 'green' channel.
                * @param[out] fact_b The correction factor for the 'blue' channel.
                * @return The correction factor.
                */
                void get_correction_factors(interp_coord_t src_x_r, interp_coord_t src_y_r,
                                            interp_coord_t src_x_g, interp_coord_t src_y_g,
                                            interp_coord_t src_x_b, interp_coord_t src_y_b,
                                            double& fact_r, double& fact_g, double& fact_b) const;

            public:
                /**
                * @brief Get the correction factors for a given position.
                * @param[in] coords The coordinates in the source image.
                * @param[out] factors The correction factors.
                */
                void get_correction_factors(const mem::CoordTupleRGB& coords,
                                            mem::ColourTupleRGB& factors) const;

            public:
                /**
                * @brief Create a clone of the correction model functionoid.
                * @return The clone.
                */
                IColourCorrectionModel* clone() const;

                /* ****************************************
                 * internals
                 * **************************************** */

            protected:
                /**
                * @brief The parameter 'a'.
                */
                double a_;

            protected:
                /**
                * @brief The parameter 'b'.
                */
                double b_;

            protected:
                /**
                * @brief The parameter 'c'.
                */
                double c_;

            protected:
                /**
                * @brief The parameter 'x0' (horizontal centre shift).
                */
                double x0_;

            protected:
                /**
                * @brief The parameter 'y0' (vertical centre shift).
                */
                double y0_;

        }; // class VignettingColourModel

        /**
        * @brief Colour correction model implementing vignetting correction.
        * @details This model is compatible with vignetting parameters used by Hugin.
        * It is the same as @ref VignettingColourModel, but compensates for the different
        * coordinate systems when parameters are set.
        */
        class HuginVignettingModel : public VignettingColourModel
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief Constructor.
                * @details In this variant, the complete information describing both the coordinate system used
                * when determining the model parameters and the coordinate system of the input image are used.
                * @param[in] param_aspect The aspect ratio that was used when determining the model parameters.
                * @param[in] input_aspect The aspect ratio of the input image.
                * @param[in] param_crop The crop factor that was used when determining the model parameters.
                * @param[in] input_crop The crop factor of the input image.
                */
                HuginVignettingModel(double param_aspect, double input_aspect,
                                     double param_crop, double input_crop);

                /**
                * @brief Constructor.
                * @details When construction the model using this constructor, the following things are
                * assumed:
                * <ol><li>The parameters were determined on an image of the same aspect ratio in landscape
                * orientation (i.e., if the input aspect is <1.0, then 1/input_aspect is assumed for the
                * parameter aspect ratio.</li>
                * <li>The image and the parameter set use the same crop factor (i.e., both factors are
                * set to 1.0).</li></ol>
                * @param[in] input_aspect The aspect ratio of the input image.
                */
                explicit HuginVignettingModel(double input_aspect);

            public:
                /**
                * @brief Set the model parameters.
                * @param[in] a The 'a' parameter.
                * @param[in] b The 'b' parameter.
                * @param[in] c The 'c' parameter.
                */
                void set_model_params(double a, double b, double c);

            public:
                /**
                * @brief Get the current model parameters.
                * @param[out] a The 'a' parameter.
                * @param[out] b The 'b' parameter.
                * @param[out] c The 'c' parameter.
                */
                void get_model_params(double& a, double& b, double& c) const;

            public:
                /**
                * @brief Create a clone of the correction model functionoid.
                * @return The clone.
                */
                IColourCorrectionModel* clone() const;

        }; // class HuginVignettingModel

    } // namespace phtr::model

} // namespace phtr

#endif // __PHTR_COLOUR_CORRECTION_MODEL_H__
