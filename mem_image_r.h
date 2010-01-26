#ifndef __MEM_IMAGE_R_H__
#define __MEM_IMAGE_R_H__

#include "image_view.h"


namespace phtr
{

    class MemImageR : public IImageViewR
    {

        public:
            virtual ~MemImageR();

        protected:
            MemImageR();

        private:
    };

} // namespace phtr

#endif // __MEM_IMAGE_R_H__
