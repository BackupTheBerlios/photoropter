namespace phtr
{

    /* ****************************************
     * nearest neighbour
     * **************************************** */

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

        if ((x_scaled < 0) || (x_scaled > width_)
                || (y_scaled < 0) || (y_scaled > height_))
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

        if ((x_scaled < 0) || (x_scaled > width_)
                || (y_scaled < 0) || (y_scaled > height_))
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

        if ((x_scaled < 0) || (x_scaled > width_)
                || (y_scaled < 0) || (y_scaled > height_))
        {
            return null_val_;
        }

        return image_view_.get_px_val_b(x_scaled, y_scaled);
    }

    /* ****************************************
     * bilinear
     * **************************************** */

    template <typename view_t>
    ImageInterpolator<Interpolation::bilinear, view_t>::ImageInterpolator
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
    ImageInterpolator<Interpolation::bilinear, view_t>::~ImageInterpolator
    ()
    {
        //NIL
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::bilinear, view_t>::
    get_px_val_r
    (interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_ + 0.5;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_ + 0.5;

        if ((x_scaled < 0) || (x_scaled > width_)
                || (y_scaled < 0) || (y_scaled > height_))
        {
            return null_val_;
        }

        // determine the edges of the 'square' in which we interpolate
        interp_coord_t x_1 = std::floor(x_scaled);
        interp_coord_t y_1 = std::floor(y_scaled);
        interp_coord_t x_2 = x_1 + 1;
        interp_coord_t y_2 = y_1 + 1;

        // edge values
        interp_channel_t val_11 = image_view_.get_px_val_r(x_1, y_1);
        interp_channel_t val_12 = image_view_.get_px_val_r(x_1, y_2);
        interp_channel_t val_21 = image_view_.get_px_val_r(x_2, y_1);
        interp_channel_t val_22 = image_view_.get_px_val_r(x_2, y_2);

        // interpolate in x direction
        interp_channel_t tmp_val_1 = (x_2 - x_scaled) * val_11 + (x_scaled - x_1) * val_21;
        interp_channel_t tmp_val_2 = (x_2 - x_scaled) * val_12 + (x_scaled - x_1) * val_22;

        // interpolate in y direction
        interp_channel_t interp_val = (y_2 - y_scaled) * tmp_val_1 + (y_scaled - y_1) * tmp_val_2;

        return interp_val;
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::bilinear, view_t>::
    get_px_val_g
    (interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_ + 0.5;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_ + 0.5;

        if ((x_scaled < 0) || (x_scaled > width_)
                || (y_scaled < 0) || (y_scaled > height_))
        {
            return null_val_;
        }

        // determine the edges of the 'square' in which we interpolate
        interp_coord_t x_1 = std::floor(x_scaled);
        interp_coord_t y_1 = std::floor(y_scaled);
        interp_coord_t x_2 = x_1 + 1;
        interp_coord_t y_2 = y_1 + 1;

        // edge values
        interp_channel_t val_11 = image_view_.get_px_val_g(x_1, y_1);
        interp_channel_t val_12 = image_view_.get_px_val_g(x_1, y_2);
        interp_channel_t val_21 = image_view_.get_px_val_g(x_2, y_1);
        interp_channel_t val_22 = image_view_.get_px_val_g(x_2, y_2);

        // interpolate in x direction
        interp_channel_t tmp_val_1 = (x_2 - x_scaled) * val_11 + (x_scaled - x_1) * val_21;
        interp_channel_t tmp_val_2 = (x_2 - x_scaled) * val_12 + (x_scaled - x_1) * val_22;

        // interpolate in y direction
        interp_channel_t interp_val = (y_2 - y_scaled) * tmp_val_1 + (y_scaled - y_1) * tmp_val_2;

        return interp_val;
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::bilinear, view_t>::
    get_px_val_b
    (interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_ + 0.5;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_ + 0.5;

        if ((x_scaled < 0) || (x_scaled > width_)
                || (y_scaled < 0) || (y_scaled > height_))
        {
            return null_val_;
        }

        // determine the edges of the 'square' in which we interpolate
        interp_coord_t x_1 = std::floor(x_scaled);
        interp_coord_t y_1 = std::floor(y_scaled);
        interp_coord_t x_2 = x_1 + 1;
        interp_coord_t y_2 = y_1 + 1;

        // edge values
        interp_channel_t val_11 = image_view_.get_px_val_b(x_1, y_1);
        interp_channel_t val_12 = image_view_.get_px_val_b(x_1, y_2);
        interp_channel_t val_21 = image_view_.get_px_val_b(x_2, y_1);
        interp_channel_t val_22 = image_view_.get_px_val_b(x_2, y_2);

        // interpolate in x direction
        interp_channel_t tmp_val_1 = (x_2 - x_scaled) * val_11 + (x_scaled - x_1) * val_21;
        interp_channel_t tmp_val_2 = (x_2 - x_scaled) * val_12 + (x_scaled - x_1) * val_22;

        // interpolate in y direction
        interp_channel_t interp_val = (y_2 - y_scaled) * tmp_val_1 + (y_scaled - y_1) * tmp_val_2;

        return interp_val;
    }

} // namespace phtr
