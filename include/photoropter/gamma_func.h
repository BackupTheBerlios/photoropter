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

namespace phtr
{
    /**
    * \brief Gamma correction functions.
    */
    namespace gamma
    {

        /**
        * \brief Interface base class for %gamma correction functions.
        */
        class IGammaFunc
        {

            public:
                /**
                * \brief Apply %gamma transformation.
                * \param[in] value The input value.
                * \return The transformed value.
                */
                virtual double gamma(double value) const = 0;

            public:
                /**
                * \brief Apply inverse %gamma transformation.
                * \param[in] value The input value.
                * \return The transformed value.
                */
                virtual double inv_gamma(double value) const = 0;

        }; // class IGammaFunc

        /**
        * \brief Generic %gamma function.
        * \details This class models the 'generic' %gamma function, i.e.:
        * \f[ x_{dst} = x_{src}^\gamma \f]
        * A %gamma value of 2.2 is the 'norm' value for current operating systems and
        * displays (although quite a lot of flatscreen differ, actually). At least in theory,
        * every image meant for display on a computer should be pre-compensated for a %gamma of
        * 2.2, with the operating system then correcting for the actual display value. In fact,
        * digital images should be pre-compensated using the sRGB %gamma function (see
        * \ref GammaSRGB), which yields roughly the same result as generic %gamma 2.2 (but not
        * quite identical).
        */
        class GammaGeneric : public IGammaFunc
        {

                /* ****************************************
                 * public interface
                 * **************************************** */

            public:
                /**
                * \brief Constructor.
                * \param[in] gam The %gamma value.
                */
                GammaGeneric(double gam);

            public:
                /**
                * \brief Apply %gamma transformation.
                * \details \f[ x_{dst}=x_{src}^\gamma \f]
                * \param[in] value The input value.
                * \return The transformed value.
                */
                virtual double gamma(double value) const;

            public:
                /**
                * \brief Apply inverse %gamma transformation.
                * \details \f[ x_{src}=x_{dst}^{1/\gamma} \f]
                * \param[in] value The input value.
                * \return The transformed value.
                */
                virtual double inv_gamma(double value) const;

                /* ****************************************
                 * internals
                 * **************************************** */

            private:
                /**
                * \brief The gamma value.
                */
                double gamma_;

        }; // class GammaGeneric

        /**
        * \brief sRGB %gamma function.
        * \details This class models the 'sRGB' %gamma function, i.e.:
        * \f[ x_{dst} = \left\{\begin{array}{ll}x_{src} / 12.92 & 0 \leq x \leq 0.04045\\
        * ((x_{src} + 0.055) / 1.055)^{2.4} & 0.04045 < x \leq 1 \end{array}\right.\f]
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
                * \brief Apply %gamma transformation.
                * \details \f[ x_{dst} = \left\{\begin{array}{ll}x_{src} / 12.92 & 0 \leq x_{src} \leq 0.04045\\
                * ((x_{src} + 0.055) / 1.055)^{2.4} & 0.04045 < x_{src} \leq 1 \end{array}\right.\f]
                * \param[in] value The input value.
                * \return The transformed value.
                */
                virtual double gamma(double value) const;

            public:
                /**
                * \brief Apply inverse %gamma transformation.
                * \details \f[ x_{src} = \left\{\begin{array}{ll}12.92\,x_{dst} & 0 \leq x_{dst} \leq 0.0031309\\
                * 1.055\,x_{dst}^{1/2.4} - 0.055 & 0.0031309 < x_{dst} \leq 1 \end{array}\right.\f]
                * \param[in] value The input value.
                * \return The transformed value.
                */
                virtual double inv_gamma(double value) const;

        }; // class GammaSRGB

        /**
        * \brief EMOR response curve.
        * \note This class implements the 'Empirical Model of Response'
        * (EMOR) for sensor response curves proposed and provided by
        * M.D. Grossberg and S.K. Nayar from the University of
        * Columbia (Computer Vision laboratory). For more information
        * on EMoR please visit
        * http://www.cs.columbia.edu/CAVE/software/softlib/dorf.php
        */
        class GammaEMOR : public IGammaFunc
        {

            private:
                /* EMoR curves */
                static const double E[];
                static const double f0[];
                static const double h01[];
                static const double h02[];
                static const double h03[];
                static const double h04[];
                static const double h05[];
                static const double h06[];
                static const double h07[];
                static const double h08[];
                static const double h09[];
                static const double h10[];
                static const double h11[];
                static const double h12[];
                static const double h13[];
                static const double h14[];
                static const double h15[];
                static const double h16[];
                static const double h17[];
                static const double h18[];
                static const double h19[];
                static const double h20[];
                static const double h21[];
                static const double h22[];
                static const double h23[];
                static const double h24[];
                static const double h25[];

                /* Inverse EMoR curves */
                static const double B[];
                static const double g0[];
                static const double hinv01[];
                static const double hinv02[];
                static const double hinv03[];
                static const double hinv04[];
                static const double hinv05[];
                static const double hinv06[];
                static const double hinv07[];
                static const double hinv08[];
                static const double hinv09[];
                static const double hinv10[];
                static const double hinv11[];
                static const double hinv12[];
                static const double hinv13[];
                static const double hinv14[];
                static const double hinv15[];
                static const double hinv16[];
                static const double hinv17[];
                static const double hinv18[];
                static const double hinv19[];
                static const double hinv20[];
                static const double hinv21[];
                static const double hinv22[];
                static const double hinv23[];
                static const double hinv24[];
                static const double hinv25[];

        }; // class GammaEMoR

    } // namespace phtr::gamma

} // namespace phtr

#endif // __PHTR_GAMMA_FUNC_H__
