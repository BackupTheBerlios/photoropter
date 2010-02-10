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

#ifndef __PHTR_IMAGE_TRANSFORM_H__
#define __PHTR_IMAGE_TRANSFORM_H__

#include <vector>

#include <photoropter/geom_correction_queue.h>
#include <photoropter/colour_correction_queue.h>

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
            ImageTransform(const typename ImageTransform::image_view_t& image_view_r, image_view_w_t& image_view_w);

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

        public:
            /**
            * \brief Access the geometry correction queue.
            * \return Reference to the queue object.
            */
            GeomCorrectionQueue& geom_queue();

        public:
            /**
            * \brief Access the colour correction queue.
            * \return Reference to the queue object.
            */
            ColourCorrectionQueue& colour_queue();

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief Apply channel clipping.
            * \param[in]  min_val  Minimal channel value.
            * \param[in]  max_val  Maximal channel value.
            * \param[out] val_r    'red' channel value.
            * \param[out] val_g    'green' channel value.
            * \param[out] val_b    'blue' channel value.
            */
            inline void clip_vals(interp_channel_t min_val,
                                  interp_channel_t max_val,
                                  interp_channel_t& val_r,
                                  interp_channel_t& val_g,
                                  interp_channel_t& val_b);

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
            /**
            * \brief The internal queue of geometrical correction models to be applied.
            */
            GeomCorrectionQueue geom_queue_;

        private:
            /**
            * \brief The internal queue of colour correction models to be applied.
            */
            ColourCorrectionQueue colour_queue_;

    }; // class ImageTransform

} // namespace phtr

#include <photoropter/image_transform.tpl.h>

#endif // __PHTR_IMAGE_TRANSFORM_H__
