namespace phr
{

    template <storage::type ty>
    image_impl<ty>::image_impl(size_t width, size_t height)
            :
            image_(width, height)
    {
        //ctor
    }

    template <storage::type ty>
    image_impl<ty>::~image_impl()
    {
        //dtor
    }

    template <storage::type ty>
    storage::type image_impl<ty>::storage_type() const
    {
        return storage_type_;
    }

} // namespace phr
