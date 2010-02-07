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

#ifndef __COLOUR_CORRECTION_QUEUE_H__
#define __COLOUR_CORRECTION_QUEUE_H__

#include <vector>

#include "types.h"
#include "channel_type.h"
#include "colour_correction_model.h"

namespace phtr
{

    /**
    * Class holding a queue of colour correction model functions.
    */
    class ColourCorrectionQueue
    {
            /* ****************************************
             * public interface
             * **************************************** */

        public:
            /**
            * \brief Standard constructor.
            * \details This will construct an empty queue.
            */
            ColourCorrectionQueue();

        public:
            /**
            * \brief Destructor.
            */
            virtual ~ColourCorrectionQueue();

        public:
            /**
            * \brief Get the correction factor for the given position and channel.
            * \oaram[in] chan  The channel (e.g., Channel::red).
            * \param[in] src_x The corresponding x coordinate for the 'red' channel
            *                  in the source image.
            * \param[in] src_y The corresponding y coordinate for the 'red' channel
            *                  in the source image.
            * \return The correction factor.
            */
            inline double get_correction_factor(Channel::type chan,
                                                interp_coord_t src_x, interp_coord_t src_y) const;

            /* ****************************************
             * internals
             * **************************************** */

        private:
            /**
            * \brief Copy constructor.
            * \note Currently deactivated (==private).
            * \param orig The original queue.
            * \details This will copy the given queue, duplicating the functionid objects.
            */
            ColourCorrectionQueue(const ColourCorrectionQueue& orig);

        private:
            /**
            * \brief Assignment operator.
            * \note Currently deactivated (==private).
            * \param orig The original queue.
            * \return Reference to the current instance.
            */
            ColourCorrectionQueue& operator=(const ColourCorrectionQueue& orig);

        private:
            /**
            * \brief Clear the current queue contents.
            */
            void clear();

        private:
            /**
            * \brief The internal list of correction models.
            */
            std::vector<IColourCorrectionModel*> correction_model_;

        private:
            /**
            * \brief The number of models currently in the queue.
            */
            unsigned short n_models_;

    };

} // namespace phtr

#include "colour_correction_queue.inl.h"

#endif // __COLOUR_CORRECTION_QUEUE_H__
