// Include standard C++ input/output library
#include <vcl_iostream.h>
#include <vxl_config.h>
#include <vil/vil_rgb.h>
#include <vil/vil_load.h>
#include <vil/vil_convert.h>
#include <vil/vil_fill.h>
#include <vil/vil_copy.h>
#include <vil/vil_image_view.h>

#include "types.h"
#include "image_view.h"
#include "image_buffer.h"
#include "channel_storage.h"

#include <memory>
#include <typeinfo>
#include <limits>

int main()
{
    using namespace phtr;
    const Storage::type storage_type(Storage::rgb_16_planar);
    typedef ChannelStorage<storage_type>::type channel_storage_t;

    std::auto_ptr<IImageBuffer> img_buf(
        IImageBuffer::get_image_buffer
        (storage_type, 100, 100)
    );

    channel_storage_t* buf = static_cast<channel_storage_t*>(img_buf->data());
    buf[0] = 65535;
    buf[10000] = 32767;
    buf[20000] = 16383;

    std::auto_ptr<IImageViewW> phtr_mem_view_w(
        ImageViewFactory::get_mem_image_view_w(
            storage_type, buf, 100, 100)
    );

    phtr_mem_view_w->write_px_val_r(50, 50, 1.0);
    phtr_mem_view_w->write_px_val_g(50, 50, 0.7);
    phtr_mem_view_w->write_px_val_b(50, 50, 0.5);

    std::auto_ptr<IImageViewIterW> phtr_iter(
        phtr_mem_view_w->get_iter(51, 50)
    );

    phtr_iter->write_px_val_r(0.1);
    phtr_iter->write_px_val_g(0.2);
    phtr_iter->write_px_val_b(0.3);

    std::auto_ptr<IImageViewR> phtr_mem_view(
        ImageViewFactory::get_mem_image_view_r(
            storage_type, buf, 100, 100)
    );

    vcl_cerr << phtr_mem_view->get_px_val_r(0, 0)
    << " " << phtr_mem_view->get_px_val_g(0, 0)
    << " " << phtr_mem_view->get_px_val_b(0, 0) << vcl_endl;

    vcl_cerr << phtr_mem_view->get_px_val_r(50, 50)
    << " " << phtr_mem_view->get_px_val_g(50, 50)
    << " " << phtr_mem_view->get_px_val_b(50, 50) << vcl_endl;

    vcl_cerr << phtr_mem_view->get_px_val_r(51, 50)
    << " " << phtr_mem_view->get_px_val_g(51, 50)
    << " " << phtr_mem_view->get_px_val_b(51, 50) << vcl_endl;

    return 0;

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

//    tiff_read_image("/home/robert/kombi1.tif",img);

    return 0;
}
