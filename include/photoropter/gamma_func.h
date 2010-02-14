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

#ifndef __PHTR_GAMMA_FUNC_H__
#define __PHTR_GAMMA_FUNC_H__

#include <cstddef>
#include <vector>
#include <photoropter/util.h>

namespace phtr
{
    /**
    * @brief Gamma correction functions.
    */
    namespace gamma
    {

        /**
        * @brief Interface base class for %gamma correction functions.
        */
        class IGammaFunc
        {

            public:
                /**
                * @brief Apply %gamma transformation.
                * @param[in] value The input value.
                * @return The transformed value.
                */
                virtual double gamma(double value) const = 0;

            public:
                /**
                * @brief Apply inverse %gamma transformation.
                * @param[in] value The input value.
                * @return The transformed value.
                */
                virtual double inv_gamma(double value) const = 0;

        }; // class IGammaFunc





        /**
        * @brief Generic %gamma function.
        * @details This class models the 'generic' %gamma function, i.e.:
        * @f[ x_{dst} = x_{src}^\gamma @f]
        * A %gamma value of 2.2 is the 'norm' value for current operating systems and
        * displays (although quite a lot of flatscreen differ, actually). At least in theory,
        * every image meant for display on a computer should be pre-compensated for a %gamma of
        * 2.2, with the operating system then correcting for the actual display value. In fact,
        * digital images should be pre-compensated using the sRGB %gamma function (see
        * @ref GammaSRGB), which yields roughly the same result as generic %gamma 2.2 (but not
        * quite identical).
        */
        class GammaGeneric : public IGammaFunc
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief Constructor.
                * @param[in] gam The %gamma value.
                */
                GammaGeneric(double gam);

            public:
                /**
                * @brief Apply %gamma transformation.
                * @details @f[ x_{dst}=x_{src}^\gamma @f]
                * @param[in] value The input value.
                * @return The transformed value.
                */
                virtual double gamma(double value) const;

            public:
                /**
                * @brief Apply inverse %gamma transformation.
                * @details @f[ x_{src}=x_{dst}^{1/\gamma} @f]
                * @param[in] value The input value.
                * @return The transformed value.
                */
                virtual double inv_gamma(double value) const;

                /* ****************************************
                 * internals
                 * **************************************** */

            private:
                /**
                * @brief The gamma value.
                */
                double gamma_;

        }; // class GammaGeneric





        /**
        * @brief sRGB %gamma function.
        * @details This class models the 'sRGB' %gamma function, i.e.:
        * @f[ x_{dst} = \left\{\begin{array}{ll}x_{src} / 12.92 & 0 \leq x \leq 0.04045\\
        * ((x_{src} + 0.055) / 1.055)^{2.4} & 0.04045 < x \leq 1 \end{array}\right.@f]
        * This %gamma function is the de facto standard for digital images.
        * It is close (but not identical) to a generic %gamma compensation with
        * a fixed value of 2.2.
        */
        class GammaSRGB : public IGammaFunc
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief Apply %gamma transformation.
                * @details @f[ x_{dst} = \left\{\begin{array}{ll}x_{src} / 12.92 & 0 \leq x_{src} \leq 0.04045\\
                * ((x_{src} + 0.055) / 1.055)^{2.4} & 0.04045 < x_{src} \leq 1 \end{array}\right.@f]
                * @param[in] value The input value.
                * @return The transformed value.
                */
                virtual double gamma(double value) const;

            public:
                /**
                * @brief Apply inverse %gamma transformation.
                * @details @f[ x_{src} = \left\{\begin{array}{ll}12.92\,x_{dst} & 0 \leq x_{dst} \leq 0.0031309\\
                * 1.055\,x_{dst}^{1/2.4} - 0.055 & 0.0031309 < x_{dst} \leq 1 \end{array}\right.@f]
                * @param[in] value The input value.
                * @return The transformed value.
                */
                virtual double inv_gamma(double value) const;

        }; // class GammaSRGB





        /**
        * @brief The EMOR response curve (base class).
        * @details This class implements the 'Empirical Model of Response'
        * (EMOR) for sensor response curves proposed and provided by
        * M.D. Grossberg and S.K. Nayar from the University of
        * Columbia (Computer Vision laboratory). For more information
        * on EMoR please visit
        * http://www.cs.columbia.edu/CAVE/software/softlib/dorf.php
        * @note EMOR is not a %gamma function per se, but can rather be
        * regarded as a concept for 'generalised' %gamma.
        * @note This base class cannot be used directly. Please use GammaEMOR and GammaInvEMOR.
        */
        class GammaEMORBase : public IGammaFunc
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief The container type of the internal parameter representation.
                */
                typedef std::vector<double> coeff_vect_t;

            public:
                /**
                * @brief The iterator type of the internal parameter representation.
                */
                typedef coeff_vect_t::iterator coeff_iter_t;

            public:
                /**
                * @brief Set the coefficients.
                * @details This method allows to set an arbitrary number of parameters by cascaded calls.
                * Example: @code set_params(1.0)(0.0)(0.1)(0.2)(0.1); @endcode
                * @note The coefficients vector is cleared first, so any remaining parameter not set will
                * be zero.
                * @param[in] param1 The first parameter.
                * @return A SetParam instance pointing to the second parameter.
                */
                util::SetParam<coeff_iter_t> set_params();

            public:
                /**
                * @brief Set the coefficients.
                * @note The coefficients vector is cleared first, so any remaining parameter not set will
                * be zero.
                * @param[in] params An iterable object (vector, list) containing the new coefficients.
                */
                template <class iterable_t>
                void set_param_list(const iterable_t& params);

                /* ****************************************
                 * internals
                 * **************************************** */

            protected:
                /**
                * @brief Standard constructor.
                * @details This initialises the EMOR function to its 'generic' form (i.e., f0 or g0).
                * All coefficients are set to 0.
                */
                GammaEMORBase();

            protected:
                /**
                * @brief The container type of precalculated value lists.
                */
                typedef std::vector<double> value_vect_t;

            protected:
                /**
                * @brief Worker function that is called by gamma() and inv_gamma().
                * @details gamma() calls get_function_value() with x and y reversed,
                * since a 'forward' gamma transformation corresponds to a backwards EMOR
                * transformation.
                */
                double get_function_value(double inp_val, const value_vect_t& xval, const value_vect_t& yval) const;

            private:
                /**
                * @brief Calculate function values and store them.
                */
                virtual void precalc_func() const = 0;

            protected:
                /**
                * @brief Internal flag to mark if function values have already been calculated (lazy init).
                */
                mutable bool precalc_done_;

            protected:
                /**
                * @brief List of 'source' values for the transformation functions.
                * @details 'x' corresponds to the irradiance level E in the EMOR model.
                */
                mutable value_vect_t xval_;

            protected:
                /**
                * @brief List of function values.
                * @details 'y' corresponds to the brightness level 'B' in the EMOR model.
                */
                mutable value_vect_t yval_;

            protected:
                /**
                * @brief The current coefficients vector.
                */
                coeff_vect_t coeff_;

            protected:
                /**
                * @brief The number of coefficients in the model (i.e., 25).
                */
                static const size_t coeff_num_ = 25;

            protected:
                /**
                * @brief The number of samples in each individual model curve.
                */
                static const size_t sample_num_ = 1024;

                /// @cond
            protected:
                static const float* h_[];
                static const float* hinv_[];

                /* EMoR curves */
                static const float E_[];
                static const float f0_[];
                static const float h01_[];
                static const float h02_[];
                static const float h03_[];
                static const float h04_[];
                static const float h05_[];
                static const float h06_[];
                static const float h07_[];
                static const float h08_[];
                static const float h09_[];
                static const float h10_[];
                static const float h11_[];
                static const float h12_[];
                static const float h13_[];
                static const float h14_[];
                static const float h15_[];
                static const float h16_[];
                static const float h17_[];
                static const float h18_[];
                static const float h19_[];
                static const float h20_[];
                static const float h21_[];
                static const float h22_[];
                static const float h23_[];
                static const float h24_[];
                static const float h25_[];

                /* Inverse EMoR curves */
                static const float B_[];
                static const float g0_[];
                static const float hinv01_[];
                static const float hinv02_[];
                static const float hinv03_[];
                static const float hinv04_[];
                static const float hinv05_[];
                static const float hinv06_[];
                static const float hinv07_[];
                static const float hinv08_[];
                static const float hinv09_[];
                static const float hinv10_[];
                static const float hinv11_[];
                static const float hinv12_[];
                static const float hinv13_[];
                static const float hinv14_[];
                static const float hinv15_[];
                static const float hinv16_[];
                static const float hinv17_[];
                static const float hinv18_[];
                static const float hinv19_[];
                static const float hinv20_[];
                static const float hinv21_[];
                static const float hinv22_[];
                static const float hinv23_[];
                static const float hinv24_[];
                static const float hinv25_[];
                /// @endcond

        }; // class GammaEMoR

        /**
        * @brief EMOR model response curve.
        * @details The coefficients for this class are compatible with e.g. the ones Hugin uses.
        * The EMOR transformation is equivalent to an inverse %gamma transformation, so there
        * can be a bit of confusion regarding the transformation direction.
        */
        class GammaEMOR : public GammaEMORBase
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief Apply %gamma transformation.
                * @note Actually, this calculates the inverse of the EMOR curve, since the
                * standard EMOR definition is equivalent to an inverse %gamma transformation.
                * @param[in] value The input value.
                * @return The transformed value.
                */
                double gamma(double value) const;

            public:
                /**
                * @brief Apply inverse %gamma transformation.
                * @note Actually, this calculates the forward EMOR transformation, since this
                * is the equivalent for the inverse %gamma transformation.
                * @param[in] value The input value.
                * @return The transformed value.
                */
                double inv_gamma(double value) const;

                /* ****************************************
                 * internals
                 * **************************************** */

            private:
                /**
                * @brief Calculate function values and store them.
                */
                void precalc_func() const;

        };

        /**
        * @brief 'Inverse' EMOR model response curve.
        * @details This class implements the gain transformation based on the 'inverse'
        * EMOR functions. The inverse definition is very similar to a classical %gamma
        * transformation; however, most programs use the 'normal' (i.e., forward) definitions,
        * so to be compatible with coefficient settings used e.g. by Hugin, use GammaEMOR instead.
        */
        class GammaInvEMOR : public GammaEMORBase
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * @brief Apply %gamma transformation.
                * @param[in] value The input value.
                * @return The transformed value.
                */
                double gamma(double value) const;

            public:
                /**
                * @brief Apply inverse %gamma transformation.
                * @param[in] value The input value.
                * @return The transformed value.
                */
                double inv_gamma(double value) const;

                /* ****************************************
                 * internals
                 * **************************************** */

            private:
                /**
                * @brief Calculate function values and store them.
                */
                void precalc_func() const;

        };

    } // namespace phtr::gamma

} // namespace phtr

#endif // __PHTR_GAMMA_FUNC_H__
