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

#ifndef __PHTR_COLOUR_CORRECTION_QUEUE_H__
#define __PHTR_COLOUR_CORRECTION_QUEUE_H__

#include <vector>

#include <photoropter/types.h>
#include <photoropter/coord_tuple.h>
#include <photoropter/colour_tuple.h>
#include <photoropter/channel_type.h>
#include <photoropter/colour_correction_model.h>

namespace phtr
{

    /**
    * @brief Class holding a queue of colour correction model functions.
    */
    class ColourCorrectionQueue
    {
            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * @brief Standard constructor.
            * @details This will construct an empty queue.
            */
            ColourCorrectionQueue();

        public:
            /**
            * @brief Destructor.
            */
            virtual ~ColourCorrectionQueue();

        public:
            /**
            * @brief Get the correction factors for a given position.
            * @param[in]  coords  The coordinates in the source image.
            * @param[out] factors The correction factors.
            */
            inline void get_correction_factors(const mem::CoordTupleRGB& coords,
                                               mem::ColourTupleRGB& factors) const;

        public:
            /**
            * @brief Add the given model to the queue.
            * @note The object will be copied; a reference to the copy is returned.
            * @param model The colour correction model to be added.
            * @return Reference to the new correction model copy.
            */
            model::IColourCorrectionModel& add_model(const model::IColourCorrectionModel& model);

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
            ColourCorrectionQueue(const ColourCorrectionQueue& orig);

        private:
            /**
            * @brief Assignment operator.
            * @note Currently deactivated (==private).
            * @param orig The original queue.
            * @return Reference to the current instance.
            */
            ColourCorrectionQueue& operator=(const ColourCorrectionQueue& orig);

        private:
            /**
            * @brief The internal list of correction models.
            */
            std::vector<model::IColourCorrectionModel*> correction_model_;

        private:
            /**
            * @brief The number of models currently in the queue.
            */
            unsigned short n_models_;

    };

} // namespace phtr

#include <photoropter/colour_correction_queue.inl.h>

#endif // __PHTR_COLOUR_CORRECTION_QUEUE_H__
