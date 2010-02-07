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

#include "Photoropter/types.h"
#include "Photoropter/channel_type.h"
#include "Photoropter/colour_correction_model.h"

namespace phtr
{

    /**
    * \brief Class holding a queue of colour correction model functions.
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
            * \brief Get the correction factors for the given position.
            * \param[in] src_x_r The corresponding x coordinate for the 'red' channel
            *                    in the source image.
            * \param[in] src_y_r The corresponding y coordinate for the 'red' channel
            *                    in the source image.
            * \param[in] src_x_g The corresponding x coordinate for the 'green' channel
            *                    in the source image.
            * \param[in] src_y_g The corresponding y coordinate for the 'green' channel
            *                    in the source image.
            * \param[in] src_x_b The corresponding x coordinate for the 'blue' channel
            *                    in the source image.
            * \param[in] src_y_b The corresponding y coordinate for the 'blue' channel
            *                    in the source image.
            * \param[out] fact_r The correction factor for the 'red' channel.
            * \param[out] fact_g The correction factor for the 'green' channel.
            * \param[out] fact_b The correction factor for the 'blue' channel.
            * \return The correction factor.
            */
            inline void get_correction_factors(interp_coord_t src_x_r, interp_coord_t src_y_r,
                                               interp_coord_t src_x_g, interp_coord_t src_y_g,
                                               interp_coord_t src_x_b, interp_coord_t src_y_b,
                                               double& fact_r, double& fact_g, double& fact_b) const;

        public:
            /**
            * \brief Add the given model to the queue.
            * \note The object will be copied.
            * \param model The colour correction model to be added.
            */
            void add_model(const IColourCorrectionModel& model);

        public:
            /**
            * \brief Clear the current queue contents.
            */
            void clear();

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

#include "Photoropter/colour_correction_queue.inl.h"

#endif // __COLOUR_CORRECTION_QUEUE_H__