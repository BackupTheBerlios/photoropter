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

#ifndef PHTR_PIXEL_CORRECTION_QUEUE_H__
#define PHTR_PIXEL_CORRECTION_QUEUE_H__

#include <vector>

#include <photoropter/types.h>
#include <photoropter/mem/coord_tuple.h>
#include <photoropter/mem/colour_tuple.h>
#include <photoropter/model/pixel_correction_model.h>

namespace phtr
{

    /**
    * @brief Class holding a queue of geometrical correction model functions.
    */
    class PixelCorrectionQueue
    {
            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief Standard constructor.
            * @details This will construct an empty queue.
            */
            PixelCorrectionQueue();

        public:
            /**
            * @brief Destructor.
            */
            virtual ~PixelCorrectionQueue();

        public:
            /**
            * @brief Get the corrected source image coordinates for the current position.
            * @param[in]  dst_x   The x coordinate "seen from" the destination image.
            * @param[in]  dst_y   The y coordinate "seen from" the destination image.
            * @param[out] coords The tuple holding the source coordinates.
            */
            inline void get_src_coords(interp_coord_t dst_x,
                                       interp_coord_t dst_y,
                                       mem::CoordTupleMono& coords) const;

        public:
            /**
            * @brief Add the given model to the queue.
            * @note The object will be copied; a reference to the copy is returned.
            * @param model The geometry correction model to be added.
            * @return Reference to the new correction model copy.
            */
            model::IPixelCorrectionModel& add_model(const model::IPixelCorrectionModel& model);

        public:
            /**
            * @brief Clear the current queue contents.
            */
            void clear();

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * @brief Copy constructor.
            * @note Currently deactivated (==private).
            * @param orig The original queue.
            * @details This will copy the given queue, duplicating the functionid objects.
            */
            PixelCorrectionQueue(const PixelCorrectionQueue& orig);

        private:
            /**
            * @brief Assignment operator.
            * @note Currently deactivated (==private).
            * @param orig The original queue.
            * @return Reference to the current instance.
            */
            PixelCorrectionQueue& operator=(const PixelCorrectionQueue& orig);

        private:
            /**
            * @brief The internal list of correction models.
            */
            std::vector<model::IPixelCorrectionModel*> correction_model_;

        private:
            /**
            * @brief The number of models currently in the queue.
            */
            unsigned short n_models_;

    }; // class PixelCorrectionQueue

} // namespace phtr

#include <photoropter/pixel_correction_queue.inl.h>

#endif // PHTR_PIXEL_CORRECTION_QUEUE_H__
