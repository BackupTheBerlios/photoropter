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

#include "correction_model_queue.h"
#include "lens_correction_model.h"

namespace phtr
{

    CorrectionModelQueue::CorrectionModelQueue()
            : n_models_(0)
    {
        //FIXME
        correction_model_.push_back(new PTLensGeomModel(0, 0.00987, -0.05127, 1, 0, 0));
        ++n_models_;
        correction_model_.push_back(new PTLensGeomModel(0, 0.00987, -0.05127, 1, 0, 0));
        ++n_models_;
        correction_model_.push_back(new PTLensGeomModel(0, 0.00987, -0.05127, 1, 0, 0));
        ++n_models_;
    }

    CorrectionModelQueue::CorrectionModelQueue(const CorrectionModelQueue& orig)
            : n_models_(0)
    {
        n_models_ = orig.correction_model_.size();
        correction_model_.resize(n_models_);

        for (size_t i = 0; i < n_models_; ++i)
        {
            correction_model_[i] = orig.correction_model_[i]->clone();
        }
    }

    CorrectionModelQueue::~CorrectionModelQueue()
    {
        this->clear();
    }

    CorrectionModelQueue& CorrectionModelQueue::operator=(const CorrectionModelQueue& orig)
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

    void CorrectionModelQueue::clear()
    {
        n_models_ = correction_model_.size();

        for (size_t i = 0; i < n_models_; ++i)
        {
            delete correction_model_[i];
        }
        correction_model_.clear();

        n_models_ = 0;
    }

} // namespace phtr
