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
        return get_px_val(Channel::red, x, y);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::
    get_px_val_g
    (interp_coord_t x, interp_coord_t y)
    {
        return get_px_val(Channel::green, x, y);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::
    get_px_val_b
    (interp_coord_t x, interp_coord_t y)
    {
        return get_px_val(Channel::blue, x, y);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::nearest_neighbour, view_t>::
    get_px_val
    (Channel::type chan, interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_;

        if ((x_scaled < 0) || (x_scaled > width_)
                || (y_scaled < 0) || (y_scaled > height_))
        {
            return null_val_;
        }

        return image_view_.get_px_val(chan, x_scaled + 0.5, y_scaled + 0.5);
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
        return get_px_val(Channel::red, x, y);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::bilinear, view_t>::
    get_px_val_g
    (interp_coord_t x, interp_coord_t y)
    {
        return get_px_val(Channel::green, x, y);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::bilinear, view_t>::
    get_px_val_b
    (interp_coord_t x, interp_coord_t y)
    {
        return get_px_val(Channel::blue, x, y);
    }

    template <typename view_t>
    interp_channel_t
    ImageInterpolator<Interpolation::bilinear, view_t>::
    get_px_val
    (Channel::type chan, interp_coord_t x, interp_coord_t y)
    {
        interp_coord_t x_scaled = (x + 0.5) * scale_x_;
        interp_coord_t y_scaled = (y + 0.5) * scale_y_;

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

        std::auto_ptr<typename view_t::iter_t> iter(image_view_.get_iter(x_1, y_1));

        /* edge values
        val_11 == val(x1, y1) -> upper left
        val_21 == val(x2, y1) -> upper right
        val_12 == val(x1, y2) -> lower left
        val_22 == val(x2, y2) -> lower right
        */
        interp_channel_t val_11 = iter->get_px_val(chan);
        iter->inc_x();
        interp_channel_t val_21 = iter->get_px_val(chan);
        iter->inc_y();
        iter->dec_x();
        interp_channel_t val_12 = iter->get_px_val(chan);
        iter->inc_x();
        interp_channel_t val_22 = iter->get_px_val(chan);

        // interpolate in x direction
        interp_channel_t tmp_val_1 = (x_2 - x_scaled) * val_11 + (x_scaled - x_1) * val_21;
        interp_channel_t tmp_val_2 = (x_2 - x_scaled) * val_12 + (x_scaled - x_1) * val_22;

        // interpolate in y direction
        interp_channel_t interp_val = (y_2 - y_scaled) * tmp_val_1 + (y_scaled - y_1) * tmp_val_2;

        return interp_val;
    }

} // namespace phtr
