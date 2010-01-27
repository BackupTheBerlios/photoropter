#ifndef __MEM_IMAGE_VIEW_R_H__
#define __MEM_IMAGE_VIEW_R_H__

#include "image_view.h"
#include "mem_storage_info.h"

#include <stdint.h>

namespace phtr
{

    class MemImageViewR : public IImageViewR
    {

        public:
            MemImageViewR (coord_t width, coord_t height);
            virtual ~MemImageViewR();

        protected:

        private:
            typedef MemStorageInfo<Storage::rgb_8_inter> storage_info_t;
            typedef storage_info_t::channel_storage_t channel_storage_t;

            storage_info_t storage_info;

            const coord_t width_;
            const coord_t height_;

            channel_storage_t* base_addr_;
            const channel_storage_t min_chan_val_;
            const channel_storage_t max_chan_val_;
            const size_t step_;
            const size_t r_offs_;
            const size_t g_offs_;
            const size_t b_offs_;
    };

} // namespace phtr

#endif // __MEM_IMAGE_VIEW_R_H__
