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

#ifndef __IMAGE_TRANSFORM_H__
#define __IMAGE_TRANSFORM_H__

#include <vector>

#include "lens_correction_model.h"

namespace phtr
{

    /**
    * \brief Image transformation class template.
    * \details Inside this class, the actual image transformation is performed.
    * \param interpolator_t The interpolator class to be used.
    * \param image_view_w_t The writing image view class to be used.
    * \param oversampling   The (over-)sampling factor.
    */
    template < typename interpolator_t, typename image_view_w_t, unsigned int oversampling = 1 >
    class ImageTransform
    {

            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief The type of the input image view.
            */
            typedef typename interpolator_t::image_view_t image_view_t;

        public:
            /**
            * \brief Constructor.
            * \param[in] image_view_r Input image view.
            * \param[in] image_view_w Output image view.
            */
            ImageTransform(const image_view_t& image_view_r, image_view_w_t& image_view_w);

        public:
            /**
            * \brief Destructor.
            */
            virtual ~ImageTransform();

        public:
            /**
            * \brief Transform the image.
            * \details The image data is read from the input image view and
            * written to the output view, while applying selected transformations.
            */
            void do_transform();

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief Internal function to fetch the transformed coordinates
            * for the current position.
            * \param[in]  dst_x   The x coordinate "seen from" the destination image.
            * \param[in]  dst_y   The y coordinate "seen from" the destination image.
            * \param[out] src_x_r The corresponding x coordinate for the 'red' channel
            *                     in the source image
            * \param[out] src_y_r The corresponding y coordinate for the 'red' channel
            *                     in the source image
            * \param[out] src_x_g The corresponding x coordinate for the 'green' channel
            *                     in the source image
            * \param[out] src_y_g The corresponding y coordinate for the 'green' channel
            *                     in the source image
            * \param[out] src_x_b The corresponding x coordinate for the 'blue' channel
            *                     in the source image
            * \param[out] src_y_b The corresponding y coordinate for the 'blue' channel
            *                     in the source image
            */
            inline void get_source_coords(interp_coord_t dst_x, interp_coord_t dst_y,
                                          interp_coord_t& src_x_r, interp_coord_t& src_y_r,
                                          interp_coord_t& src_x_g, interp_coord_t& src_y_g,
                                          interp_coord_t& src_x_b, interp_coord_t& src_y_b);

        private:
            /**
            * \brief Internal interpolator object.
            * \details The interpolator uses the input view given in the constructor.
            */
            interpolator_t interpolator_;

        private:
            /**
            * \brief Internal output image view object.
            */
            image_view_w_t& image_view_w_;

        private:
            std::vector<ILensCorrectionModel*> correction_model_;
            unsigned short n_models_;

    }; // class ImageTransform

} // namespace phtr

#include "image_transform.tpl.h"

#endif // __IMAGE_TRANSFORM_H__
