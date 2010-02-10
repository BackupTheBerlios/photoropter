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

#ifndef __PHTR_GEOM_CORRECTION_MODEL_H__
#define __PHTR_GEOM_CORRECTION_MODEL_H__

#include <photoropter/types.h>
#include <photoropter/correction_model_base.h>

namespace phtr
{

    /**
    * \brief Interface base class for geometrical lens correction models.
    * \details The corrections models are implemented using a 'functionid' pattern.
    */
    class IGeomCorrectionModel
    {

        public:
            /**
            * \brief Get the corrected source image coordinates for the current position.
            * \param[in,out] x_r The corresponding x coordinate for the 'red' channel
            *                    in the source image.
            * \param[in,out] y_r The corresponding y coordinate for the 'red' channel
            *                    in the source image.
            * \param[in,out] x_g The corresponding x coordinate for the 'green' channel
            *                    in the source image.
            * \param[in,out] y_g The corresponding y coordinate for the 'green' channel
            *                    in the source image.
            * \param[in,out] x_b The corresponding x coordinate for the 'blue' channel
            *                    in the source image.
            * \param[in,out] y_b The corresponding y coordinate for the 'blue' channel
            *                    in the source image.
            */
            virtual void get_src_coords(interp_coord_t& x_r, interp_coord_t& y_r,
                                        interp_coord_t& x_g, interp_coord_t& y_g,
                                        interp_coord_t& x_b, interp_coord_t& y_b) const = 0;

        public:
            /**
            * \brief Create a clone of the correction model functionoid.
            * \return The clone.
            */
            virtual IGeomCorrectionModel* clone() const = 0;

    }; // class IGeomCorrectionModel

    /**
    * \brief The PTLens geometric correction model.
    * \details The PTLens correction model implements the following formula: \f[
    * r_{src} = (a r_{dst}^3 + b r_{dst}^2 + c r_{dst} + d)  r_{dst}
    * \f]
    * Usually, 'd' is left at a fixed value of 1. Additionally, coordinates
    * describing a shift of the center are often used. Hugin and PanoTools usually
    * call these 'd' and 'e', thus creating a bit of a confusion concerning the 'd'
    * parameter in the formula above. Because of that, we will use the format
    * (x0,y0) to designate the center shift.
    */
    class PTLensGeomModel : public IGeomCorrectionModel, private CorrectionModelBase
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief Constructor.
            * \details In this variant, the complete information describing both the coordinate system used
            * when determining the model parameters and the coordinate system of the input image are used.
            * \param[in] param_aspect The aspect ratio that was used when determining the model parameters.
            * \param[in] input_aspect The aspect ratio of the input image.
            * \param[in] param_crop The crop factor that was used when determining the model parameters.
            * \param[in] input_crop The crop factor of the input image.
            */
            PTLensGeomModel(double param_aspect, double input_aspect,
                            double param_crop, double input_crop);

        public:
            /**
            * \brief Constructor.
            * \details When construction the model using this constructor, the following things are
            * assumed:
            * <ol><li>The parameters were determined on an image of the same aspect ratio in landscape
            * orientation (i.e., if the input aspect is <1.0, then 1/input_aspect is assumed for the
            * parameter aspect ratio.</li>
            * <li>The image and the parameter set use the same crop factor (i.e., both factors are
            * set to 1.0).</li></ol>
            * \param[in] input_aspect The aspect ratio of the input image.
            */
            explicit PTLensGeomModel(double input_aspect);

        public:
            /**
            * \brief Set the model parameters.
            * \param[in] a The 'a' parameter.
            * \param[in] b The 'b' parameter.
            * \param[in] c The 'c' parameter.
            * \param[in] d The 'd' parameter.
            * \param[in] x0 The 'x0' parameter (horizontal center shift).
            * \param[in] y0 The 'y0' parameter (vertical center shift).
            * \note Both x0 and y0 are not considered 'lens parameters' but rather camera/sensor
            * parameters. They are therefore \em not transformed in any way, but always interpeted
            * normalised Photoropter coordinate system.
            */
            void set_model_params(double a, double b, double c, double d,
                                  interp_coord_t x0 = 0, interp_coord_t y0 = 0);

        public:
            /**
            * \brief Set the model parameters.
            * \param[in] a The 'a' parameter.
            * \param[in] b The 'b' parameter.
            * \param[in] c The 'c' parameter.
            * \param[in] d The 'd' parameter.
            * \param[in] x0 The 'x0' parameter (horizontal center shift).
            * \param[in] y0 The 'y0' parameter (vertical center shift).
            * \note Both x0 and y0 are not considered 'lens parameters' but rather camera/sensor
            * parameters. They are therefore \em not transformed in any way, but always interpeted
            * normalised Photoropter coordinate system.
            */
            void get_model_params(double& a, double& b, double& c, double& d,
                                  interp_coord_t& x0, interp_coord_t& y0) const;

        public:
            /**
            * \brief Set the model parameters.
            * \param[in] a The 'a' parameter.
            * \param[in] b The 'b' parameter.
            * \param[in] c The 'c' parameter.
            * \param[in] d The 'd' parameter.
            */
            void get_model_params(double& a, double& b, double& c, double& d) const;

        public:
            /**
            * \brief Get the corrected source image coordinates for the current position.
            * \param[in,out] x_r The corresponding x coordinate for the 'red' channel
            *                     in the source image.
            * \param[in,out] y_r The corresponding y coordinate for the 'red' channel
            *                     in the source image.
            * \param[in,out] x_g The corresponding x coordinate for the 'green' channel
            *                     in the source image.
            * \param[in,out] y_g The corresponding y coordinate for the 'green' channel
            *                     in the source image.
            * \param[in,out] x_b The corresponding x coordinate for the 'blue' channel
            *                     in the source image.
            * \param[in,out] y_b The corresponding y coordinate for the 'blue' channel
            *                     in the source image.
            */
            void get_src_coords(interp_coord_t& x_r, interp_coord_t& y_r,
                                interp_coord_t& x_g, interp_coord_t& y_g,
                                interp_coord_t& x_b, interp_coord_t& y_b) const;

        public:
            /**
            * \brief Create a clone of the correction model functionoid.
            * \return The clone.
            */
            IGeomCorrectionModel* clone() const;

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief The parameter 'a'.
            */
            double a_;

        private:
            /**
            * \brief The parameter 'b'.
            */
            double b_;

        private:
            /**
            * \brief The parameter 'c'.
            */
            double c_;

        private:
            /**
            * \brief The parameter 'd'.
            */
            double d_;

        private:
            /**
            * \brief The parameter 'x0'.
            */
            double x0_;

        private:
            /**
            * \brief The parameter 'y0'.
            */
            double y0_;

    }; // class PTLensGeomModel

} // namespace phtr

#endif // __PHTR_GEOM_CORRECTION_MODEL_H__
