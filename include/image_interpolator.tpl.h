namespace phtr
{

    template <typename view_t>
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::ImageInterpolator(view_t* image_view)
            : image_view_(image_view)
    {
        scale_x_ = static_cast<interp_coord_t>(image_view_->width()) - 1;
        scale_y_ = static_cast<interp_coord_t>(image_view_->height() - 1);
    }

    template <typename view_t>
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::~ImageInterpolator()
    {
        //NIL
    }

    template <typename view_t>
    channel_t ImageInterpolator<Interpolation::nearest_neighbour, view_t>::get_px_val_r(interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_;

        // FIXME
        return image_view_->get_px_val_r(x_scaled, y_scaled);
    }


} // namespace phtr
