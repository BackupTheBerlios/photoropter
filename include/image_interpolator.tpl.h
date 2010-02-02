namespace phtr
{

    template <typename view_t>
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::ImageInterpolator
    (const view_t& image_view)
            : image_view_(image_view),
            width_(image_view_.width()),
            height_(image_view_.height()),
            null_val_(0)
    {
        scale_x_ = static_cast<interp_coord_t>(image_view_.width()) - 1;
        scale_y_ = static_cast<interp_coord_t>(image_view_.height() - 1);
    }

    template <typename view_t>
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::~ImageInterpolator
    ()
    {
        //NIL
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::
    get_px_val_r
    (interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_ + 0.5;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_ + 0.5;

        if ((x_scaled < 0) or(x_scaled > width_)
                or(y_scaled < 0) or(y_scaled > height_))
        {
            return null_val_;
        }

        return image_view_.get_px_val_r(x_scaled, y_scaled);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::
    get_px_val_g
    (interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_ + 0.5;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_ + 0.5;

        if ((x_scaled < 0) or(x_scaled > width_)
                or(y_scaled < 0) or(y_scaled > height_))
        {
            return null_val_;
        }

        return image_view_.get_px_val_g(x_scaled, y_scaled);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::
    get_px_val_b
    (interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_ + 0.5;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_ + 0.5;

        if ((x_scaled < 0) or(x_scaled > width_)
                or(y_scaled < 0) or(y_scaled > height_))
        {
            return null_val_;
        }

        return image_view_.get_px_val_b(x_scaled, y_scaled);
    }

} // namespace phtr
