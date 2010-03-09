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

#include <cmath>

#include <photoropter/model/pixel_correction_model.h>
#include <photoropter/model/subpixel_correction_model.h>
#include <photoropter/model/correction_model_base.h>
#include <photoropter/geometry_type.h>
#include <photoropter/geom/rectilinear.h>
#include <photoropter/geom/fisheye_equidist.h>
#include <photoropter/geom/fisheye_equisolid.h>
#include <photoropter/geom/fisheye_stereo.h>
#include <photoropter/geom/fisheye_ortho.h>

namespace phtr
{

    namespace model
    {

        /**
         * @brief Interface class for the geometry conversion %model class template.
         */
        class IGeometryConvertPixelModel : public IPixelCorrectionModel
        {
            public:
                /**
                 * @brief (Dummy) destructor.
                 */
                virtual ~IGeometryConvertPixelModel() {}

            public:
                /**
                * @brief Set the lens focal lengths.
                * @ref mem::MemLayout template, e.g. mem::MemLayout<mem::Storage::rgb_8_inter>::idx_red
                * @param[in] src_focal_length The source focal length.
                * @param[in] dst_focal_length The destination focal length.
                */
                virtual void set_focal_lengths(double src_focal_length, double dst_focal_length) = 0;
        };

        /**
        * @brief A geometric %model to perform geometry conversion.
        * @details Usually you will not use this template directly, but
        * create instances through @ref get_geometry_conversion().
        * @param src_model_T The source geometry.
        * @param dst_model_T The destination geometry.
        */
        template <typename src_model_T, typename dst_model_T>
        class GeometryConvertPixelModel
                    : private CorrectionModelBase,
                    public IGeometryConvertPixelModel
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
                * @param[out] x0 The 'x0' parameter (horizontal centre shift).
                * @param[out] y0 The 'y0' parameter (vertical centre shift).
                */
                void get_centre_shift(interp_coord_t& x0, interp_coord_t& y0) const;

            public:
                /**
                * @brief Get the corrected source image coordinates for the current position.
                * @note This function changes the input tuple.
                * @param[in,out] coords The coordinates tuple.
                */
                void get_src_coords(mem::CoordTupleMono& coords) const;

            public:
                /**
                * @brief Create a clone of the correction %model functionoid.
                * @return The clone.
                */
                GeometryConvertPixelModel* clone() const;

                /* ****************************************
                * internals
                * **************************************** */

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

                /**
                 * @brief The source geometry.
                 */
                src_model_T src_geom_;

                /**
                 * @brief The destination geometry.
                 */
                dst_model_T dst_geom_;

        }; // class GeometryConvertPixelModel

        /**
         * @brief Internal function template to instantiate a matching geometry conversion object.
         * @private
         * @note This template is not supposed to be used 'from the outside'.
         * @param src_geom_T   The source geometry.
         * @param dst_geom     The destination geometry.
         * @param input_aspect The aspect ratio of the image.
         * @param input_crop   The crop factor of the image.
         */
        template <typename src_geom_T>
        IGeometryConvertPixelModel* do_get_geometry_conversion(Geometry::type dst_geom,
                double input_aspect,
                double input_crop);

        /**
         * @brief Function to instantiate a matching @ref GeometryConvertPixelModel<>
         * geometry conversion object.
         * @param src_geom     The source geometry.
         * @param dst_geom     The destination geometry.
         * @param input_aspect The aspect ratio of the image.
         * @param input_crop   The crop factor of the image.
         */
        IGeometryConvertPixelModel* get_geometry_conversion(Geometry::type src_geom, Geometry::type dst_geom,
                double input_aspect, double input_crop);

    } // namespace phtr::model

} // namespace phtr

#include <photoropter/model/geometry_convert_pixel_model.tpl.h>

#endif // PHTR_GEOMETRY_CONVERT_PIXEL_MODEL_H__
