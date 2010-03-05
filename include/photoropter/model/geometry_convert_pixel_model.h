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

#ifndef PHTR_GEOMETRY_CONVERT_PIXEL_MODEL_H__
#define PHTR_GEOMETRY_CONVERT_PIXEL_MODEL_H__

#include <photoropter/model/subpixel_correction_model.h>
#include <photoropter/model/correction_model_base.h>
#include <photoropter/geometry/fisheye_equisolid.h>

namespace phtr
{

    namespace model
    {

        /**
        * @brief A geometric %model to perform geometry conversion.
        */
        class GeometryConvertPixelModel
                    : public ISubpixelCorrectionModel,
                    private CorrectionModelBase
        {

                /* ****************************************
                * public interface
                * **************************************** */

            public:
                /**
                * @brief Constructor.
                * @param[in] input_aspect The aspect ratio of the input image.
                * @param[in] input_crop The crop factor of the input image.
                */
                GeometryConvertPixelModel(double input_aspect, double input_crop);

            public:
                /**
                * @brief Set the lens focal lengths.
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[in] src_focal_length The source focal length.
                * @param[in] dst_focal_length The destination focal length.
                */
                void set_focal_lengths(double src_focal_length, double dst_focal_length);

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
                * @param[out] x0       The 'x0' parameter (horizontal centre shift).
                * @param[out] y0       The 'y0' parameter (vertical centre shift).
                */
                void get_centre_shift(interp_coord_t& x0, interp_coord_t& y0) const;

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
                ISubpixelCorrectionModel* clone() const;

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
                * @brief Calculate the internal coordinate system compensation factor.
                */
                virtual void calc_coord_fact();

            private:
                /**
                * @brief The parameter 'x0'.
                */
                double x0_;

            private:
                /**
                * @brief The parameter 'y0'.
                */
                double y0_;

                typedef geometry::FisheyeEquisolid src_model_T;
                typedef geometry::FisheyeEquisolid dst_model_T;
                src_model_T src_model_;
                dst_model_T dst_model_;

        }; // class GeometryConvertPixelModel

    } // namespace phtr::model

} // namespace phtr

#endif // PHTR_GEOMETRY_CONVERT_PIXEL_MODEL_H__
