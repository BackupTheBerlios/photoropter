#include "image_view.h"

namespace phtr
{

    channel_t IImageViewR::get_px_val(Channel::type chan, coord_t x, coord_t y) const
    {
        switch (chan)
        {

            case Channel::red:
                return get_px_val_r(x, y);
                break;

            case Channel::green:
                return get_px_val_g(x, y);
                break;

            case Channel::blue:

            default:
                return get_px_val_b(x, y);
                break;
        }
    }

} // namespace phtr
