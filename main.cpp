// Include standard C++ input/output library
#include <vcl_iostream.h>
#include <vxl_config.h>
#include <vil/vil_rgb.h>
#include <vil/vil_load.h>
#include <vil/vil_convert.h>
#include <vil/vil_fill.h>
#include <vil/vil_copy.h>
#include <vil/vil_image_view.h>

#include <boost/gil/gil_all.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/color_convert.hpp>
#include <boost/gil/pixel.hpp>

#include "image_view.h"

#include <typeinfo>
#include <limits>

using namespace boost::gil;

int main()
{
    vcl_cout << "Loading image."  << vcl_endl;
    vil_image_resource_sptr img_rsc = vil_load_image_resource("/home/robert/kombi1.tif");

    typedef vxl_uint_32 channel_t;

    vcl_cout << "Converting to 32bit int."  << vcl_endl;
    vil_image_view_base_sptr img_planes =
        vil_convert_to_n_planes(4,
                                vil_convert_stretch_range(channel_t(),
                                                          img_rsc->get_view()
                                                         )
                               );
    // create interim view of the alpha plane (select 1 plane, starting with 3)
    vil_image_view<channel_t> alpha = vil_planes(vil_image_view<channel_t> (img_planes), 3, 1, 1);
    // set alpha to white
    vil_fill(alpha, std::numeric_limits<channel_t>::max());
    // convert to component order
    vcl_cout << "Converting to component order."  << vcl_endl;
    vil_image_view<vil_rgba<channel_t> > img_view =
        vil_convert_to_component_order(img_planes);
    //vil_image_view<vxl_int_32> alpha = vil_planes(img_view, 3, 1, 1);

    size_t width = img_view.ni();
    size_t height = img_view.nj();
    unsigned int nplanes = img_view.nplanes();

    vcl_cerr << "Dimensions: " << width << " x " << height << " x " << nplanes << vcl_endl;

    // fetch pixel falue
    const vil_rgba<channel_t>& pixel = img_view(100, 100);
    vcl_cerr << "Pixel (100, 100) = "
    << pixel.R() << ", "
    << pixel.G() << ", "
    << pixel.B() << ", "
    << pixel.A() << vcl_endl;

    //////////////////////////////
    // GIL stuff

    // create GIL image
    vcl_cerr << "Creating GIL image." << vcl_endl;
    rgba32_image_t gil_img(width, height);
    rgba32_view_t gil_view = gil_img._view;

    // get a pointer and create parasitic VIL view
    vil_rgba<channel_t>* gil_ptr = reinterpret_cast<vil_rgba<channel_t>*>(
                                       interleaved_view_get_raw_data(gil_img._view)
                                   );
    vil_image_view<vil_rgba<channel_t> > transfer_view(gil_ptr, width, height, 1, 1, width, 1);

    vcl_cerr << "Copying data to GIL image." << vcl_endl;
    transfer_view.deep_copy(img_view);

    vcl_cerr << gil_view(100, 100)[0] << ", "
    << gil_view(100, 100)[1] << ", "
    << gil_view(100, 100)[2] << ", "
    << gil_view(100, 100)[3] << vcl_endl;

    typedef boost::gil::pixel<boost::gil::channel_type<rgba32_image_t>::type, gray_layout_t> gray_pixel_t;
    typedef color_converted_view_type<rgba32_view_t, gray_pixel_t>::type gray_conv_view_t;

    const gray_conv_view_t& gray_conv_view = boost::gil::color_converted_view<gray_pixel_t> (gil_view);

    vcl_cerr << gray_conv_view.width() << "," << gray_conv_view.height() << vcl_endl;
    vcl_cerr << (uint32_t) gray_conv_view(100, 100)[0] << vcl_endl;

//    tiff_read_image("/home/robert/kombi1.tif",img);

    return 0;
}
