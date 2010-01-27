#ifndef __MEM_IMAGE_VIEW_R_H__
#define __MEM_IMAGE_VIEW_R_H__

#include "image_view.h"

#include <stdint.h>

namespace phtr
{

    class MemImageViewR : public IImageViewR
    {

        public:
            MemImageViewR (size_t width, size_t height);
            virtual ~MemImageViewR();

        protected:

        private:
            typedef uint8_t channel_storage_t;

            size_t width_;
            size_t height_;

            channel_storage_t* base_addr_;
            channel_storage_t min_chan_val_;
            channel_storage_t max_chan_val_;
            size_t step;
            size_t r_offs_;
            size_t g_offs_;
            size_t b_offs_;
    };

} // namespace phtr

#endif // __MEM_IMAGE_VIEW_R_H__
