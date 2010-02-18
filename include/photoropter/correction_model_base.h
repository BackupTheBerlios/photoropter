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

#ifndef __PHTR_CORRECTION_MODEL_BASE_H__
#define __PHTR_CORRECTION_MODEL_BASE_H__

namespace phtr
{

    /**
    * @brief Correction models.
    */
    namespace model
    {

        /**
         * @brief Lens correction model base class.
         * @details This class deals mainly with the differences in coordinate systems
         * (different aspect ratios, crop factors) and is not supposed to be used directly.
         */
        class CorrectionModelBase
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief Reset the coordinate system parameters.
                * @note Calling this function does not reset the current model parameters. Call
                * the appropriate set_model_params() function (or similar) afterwards to ensure a
                * correct parameter set.
                * @param[in] param_aspect The aspect ratio that was used when determining the model parameters.
                * @param[in] input_aspect The aspect ratio of the input image.
                * @param[in] param_crop The crop factor that was used when determining the model parameters.
                * @param[in] input_crop The crop factor of the input image.
                */
                void set_coord_params(double param_aspect, double input_aspect,
                                      double param_crop, double input_crop);

                /* ****************************************
                 * internals
                 * **************************************** */

                ///@cond PROTECTED
            protected:
                /**
                * @brief Constructor.
                * @details In this variant, the complete information describing both the coordinate system used
                * when determining the model parameters and the coordinate system of the input image are used.
                * @param[in] param_aspect The aspect ratio that was used when determining the model parameters.
                * @param[in] input_aspect The aspect ratio of the input image.
                * @param[in] param_crop The crop factor that was used when determining the model parameters.
                * @param[in] input_crop The crop factor of the input image.
                */
                CorrectionModelBase(double param_aspect, double input_aspect,
                                    double param_crop, double input_crop);

            protected:
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
                explicit CorrectionModelBase(double input_aspect);

            protected:
                /**
                * @brief Calculate the internal coordinate system compensation factor.
                */
                virtual void calc_coord_fact();

            protected:
                /**
                * @brief The aspect ratio that was used when determining the model parameters.
                */
                double param_aspect_;

            protected:
                /**
                * @brief The aspect ratio of the input image.
                */
                double input_aspect_;

            protected:
                /**
                * @brief The crop factor that was used when determining the model parameters.
                */
                double param_crop_;

            protected:
                /**
                * @brief The crop factor of the input image.
                */
                double input_crop_;

            protected:
                /**
                * @brief The coordinate scaling factor.
                */
                double coord_fact_;
                ///@endcond

        }; // CorrectionModelBase

    } // namespace phtr::model

} // namespace phtr

#endif // __PHTR_CORRECTION_MODEL_BASE_H__
