#include "image_interpolator.h"

namespace phtr
{

    ImageInterpolator::ImageInterpolator(MemImageViewR<Storage::rgb_16_planar>* image_view)
            : image_view_(image_view)
    {
        scale_x_ = static_cast<interp_coord_t>(image_view_->width()) - 1;
        scale_y_ = static_cast<interp_coord_t>(image_view_->height() - 1);
    }

    ImageInterpolator::~ImageInterpolator()
    {
        //NIL
    }

    channel_t ImageInterpolator::get_px_val_r(interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_;

        // FIXME
        return image_view_->get_px_val_r(x_scaled, y_scaled);
    }


} // namespace phtr
