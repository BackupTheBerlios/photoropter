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

#include <photoropter/geom_correction_queue.h>
#include <photoropter/model/geom_correction_model.h>

namespace phtr
{

    GeomCorrectionQueue::GeomCorrectionQueue()
            : n_models_(0)
    {
        //NIL
    }

    GeomCorrectionQueue::GeomCorrectionQueue(const GeomCorrectionQueue& orig)
            : n_models_(0)
    {
        n_models_ = orig.correction_model_.size();
        correction_model_.resize(n_models_);

        for (size_t i = 0; i < n_models_; ++i)
        {
            correction_model_[i] = orig.correction_model_[i]->clone();
        }
    }

    GeomCorrectionQueue::~GeomCorrectionQueue()
    {
        this->clear();
    }

    GeomCorrectionQueue& GeomCorrectionQueue::operator=(const GeomCorrectionQueue& orig)
    {
        this->clear();

        n_models_ = orig.correction_model_.size();
        correction_model_.resize(n_models_);

        for (size_t i = 0; i < n_models_; ++i)
        {
            correction_model_[i] = orig.correction_model_[i]->clone();
        }

        return *this;
    }

    void GeomCorrectionQueue::clear()
    {
        n_models_ = correction_model_.size();

        for (size_t i = 0; i < n_models_; ++i)
        {
            delete correction_model_[i];
        }
        correction_model_.clear();

        n_models_ = 0;
    }

    model::IGeomCorrectionModel& GeomCorrectionQueue::add_model(const model::IGeomCorrectionModel& model)
    {
        model::IGeomCorrectionModel* new_mod = model.clone();

        correction_model_.push_back(new_mod);
        ++n_models_;

        return *new_mod;
    }

} // namespace phtr
