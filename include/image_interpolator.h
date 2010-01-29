#ifndef __IMAGEINTER_POLATOR_H__
#define __IMAGEINTER_POLATOR_H__

#include "image_view.h"
#include "types.h"

namespace phtr
{

    class ImageInterpolator
    {
        public:
            ImageInterpolator(IImageViewR* image_view);
            virtual ~ImageInterpolator();

        public:
            channel_t get_px_val_r(interp_coord_t x, interp_coord_t y);

        private:
            IImageViewR* image_view_;

        private:
            channel_t scale_x_;

        private:
            channel_t scale_y_;

    }; // class ImageInterpolator

} // namespace phtr

#endif // __IMAGEINTER_POLATOR_H__
