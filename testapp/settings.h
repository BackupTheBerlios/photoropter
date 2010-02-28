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
            ptlens_params(5, 0),
            vignetting_corr(false),
            vignetting_params(5, 0),
            param_aspect(0),
            param_crop(1.0),
            image_crop(1.0),
            sub_rect(false),
            sub_rect_x0(0),
            sub_rect_y0(0),
            sub_rect_w(0),
            sub_rect_h(0),
            gamma(2.2),
            gainfunc(GainFunc::srgb),
            oversampling(1),
            interp_type(Interpolation::bilinear),
            lanczos_support(2)
    {}

    bool ptlens_corr;
    std::vector<double> ptlens_params;
    bool vignetting_corr;
    std::vector<double> vignetting_params;
    double param_aspect;
    double param_crop;
    double image_crop;
    bool sub_rect;
    size_t sub_rect_x0;
    size_t sub_rect_y0;
    size_t sub_rect_w;
    size_t sub_rect_h;
    double gamma;
    std::string inp_file;
    std::string outp_file;

    GainFunc::type gainfunc;
    std::vector<double> emor_coeffs;

    unsigned oversampling;
    Interpolation::type interp_type;
    unsigned lanczos_support;
};

#endif // PHTRTEST_SETTINGS_H__
