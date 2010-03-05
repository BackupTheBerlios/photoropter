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

#include <list>

#include <photoropter/pixel_correction_queue.h>
#include <photoropter/model/pixel_correction_model.h>

namespace phtr
{

    PixelCorrectionQueue::PixelCorrectionQueue()
            : n_models_(0)
    {
        //NIL
    }

    PixelCorrectionQueue::PixelCorrectionQueue(const PixelCorrectionQueue& orig)
            : n_models_(0)
    {
        n_models_ = static_cast<unsigned short>(orig.correction_model_.size());
        correction_model_.resize(n_models_);

        for (size_t i = 0; i < n_models_; ++i)
        {
            correction_model_[i] = orig.correction_model_[i]->clone();
        }
    }

    PixelCorrectionQueue::~PixelCorrectionQueue()
    {
        this->clear();
    }

    PixelCorrectionQueue& PixelCorrectionQueue::operator=(const PixelCorrectionQueue& orig)
    {
        this->clear();

        n_models_ = static_cast<unsigned short>(orig.correction_model_.size());
        correction_model_.resize(n_models_);

        for (size_t i = 0; i < n_models_; ++i)
        {
            correction_model_[i] = orig.correction_model_[i]->clone();
        }

        return *this;
    }

    void PixelCorrectionQueue::clear()
    {
        n_models_ = static_cast<unsigned short>(correction_model_.size());

        for (size_t i = 0; i < n_models_; ++i)
        {
            delete correction_model_[i];
        }
        correction_model_.clear();

        n_models_ = 0;
    }

    model::IPixelCorrectionModel& PixelCorrectionQueue::add_model(const model::IPixelCorrectionModel& model)
    {
        model::IPixelCorrectionModel* new_mod = model.clone();

        std::list<model::IPixelCorrectionModel*> tmp_list(correction_model_.begin(), correction_model_.end());
        tmp_list.push_front(new_mod);

        correction_model_.assign(tmp_list.begin(), tmp_list.end());
        ++n_models_;

        return *new_mod;
    }

} // namespace phtr
