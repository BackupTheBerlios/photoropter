#ifndef __MEM_IMAGE_VIEW_R_H__
#define __MEM_IMAGE_VIEW_R_H__

#include "image_view.h"

namespace phtr
{

class MemImageViewR : public IImageViewR
{
    public:
        MemImageViewR();
        virtual ~MemImageViewR();
    protected:
    private:
};

} // namespace phtr

#endif // __MEM_IMAGE_VIEW_R_H__
