/*

  phtrtest: Photoropter demo application

  Copyright (C) 2010 Robert Fendt

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef PHTRTEST_SETTINGS_H__
#define PHTRTEST_SETTINGS_H__

struct Interpolation
{
    enum type
    {
        nearest_neighbour,
        bilinear,
        lanczos
    };
};

struct GainFunc
{
    enum type
    {
        srgb,
        gamma,
        emor,
        invemor
    };
};

struct Settings
{
    Settings()
            : ptlens_corr(false),
            ptlens_params(3, 0),
            vignetting_corr(false),
            vignetting_params(3, 0),
            x0(0),
            y0(0),
            param_aspect_override(false),
            param_aspect(1.0),
            param_crop(1.0),
            image_crop(1.0),
            sub_rect(false),
            sub_rect_x0(0),
            sub_rect_y0(0),
            sub_rect_w(0),
            sub_rect_h(0),
            gainfunc(GainFunc::srgb),
            gamma(2.2),
            oversampling(1),
            interp_type(Interpolation::bilinear),
            lanczos_support(2)
    {}

    // perform PTLens correction?
    bool ptlens_corr;
    std::vector<double> ptlens_params;

    // perform vignetting correction?
    bool vignetting_corr;
    std::vector<double> vignetting_params;

    // centre shift
    double x0;
    double y0;

    // parameter aspect, crop factor etc.
    bool param_aspect_override;
    double param_aspect;
    double param_crop;
    double image_crop;

    // clip rectangle
    bool sub_rect;
    size_t sub_rect_x0;
    size_t sub_rect_y0;
    size_t sub_rect_w;
    size_t sub_rect_h;

    // input / output file names
    std::string inp_file;
    std::string outp_file;

    // gain function (i.e., gamma etc)
    GainFunc::type gainfunc;
    double gamma;
    std::vector<double> emor_coeffs;

    // interpolation / oversampling
    unsigned oversampling;
    Interpolation::type interp_type;
    unsigned lanczos_support;
};

#endif // PHTRTEST_SETTINGS_H__
