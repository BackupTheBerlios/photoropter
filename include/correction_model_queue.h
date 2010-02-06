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

#ifndef __CORRECTION_MODEL_QUEUE_H__
#define __CORRECTION_MODEL_QUEUE_H__

#include <vector>

#include "types.h"
#include "lens_correction_model.h"

namespace phtr
{

    /**
    * Class holding a queue of lens correction model functions.
    */
    class CorrectionModelQueue
    {
            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief Standard constructor.
            * \details This will construct an empty queue.
            */
            CorrectionModelQueue();

        private:
            /**
            * \brief Copy constructor.
            * \note Currently deactivated (==private).
            * \param orig The original queue.
            * \details This will copy the given queue, duplicating the functionid objects.
            */
            CorrectionModelQueue(const CorrectionModelQueue& orig);

        public:
            /**
            * \brief Destructor.
            */
            virtual ~CorrectionModelQueue();

        private:
            /**
            * \brief Assignment operator.
            * \note Currently deactivated (==private).
            * \param orig The original queue.
            * \return Reference to the current instance.
            */
            CorrectionModelQueue& operator=(const CorrectionModelQueue& orig);

        public:
            /**
            * \brief Fetch the transformed coordinates for the given position.
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
                                          interp_coord_t& src_x_b, interp_coord_t& src_y_b) const;

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief Clear the current queue contents.
            */
            void clear();

        private:
            /**
            * \brief The internal list of correction models.
            */
            std::vector<ILensCorrectionModel*> correction_model_;

        private:
            /**
            * \brief The number of models currently in the queue.
            */
            unsigned short n_models_;

    };

} // namespace phtr

#include "correction_model_queue.inl.h"

#endif // __CORRECTION_MODEL_QUEUE_H__
