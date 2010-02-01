// Include standard C++ input/output library
#include <vcl_iostream.h>
#include <vxl_config.h>
#include <vil/vil_rgb.h>
#include <vil/vil_load.h>
#include <vil/vil_save.h>
#include <vil/vil_convert.h>
#include <vil/vil_fill.h>
#include <vil/vil_copy.h>
#include <vil/vil_image_view.h>

#include "types.h"
#include "mem_image_view_r.h"
#include "mem_image_view_w.h"
#include "image_buffer.h"
#include "channel_storage.h"
#include "image_interpolator.h"
#include "image_transform.h"

#include <memory>
#include <typeinfo>
#include <limits>

int main()
{
    using namespace phtr;

    const Storage::type storage_type(Storage::rgb_16_planar);
    typedef ChannelStorage<storage_type>::type channel_storage_t;

    typedef ImageBuffer<storage_type> buffer_t;
    typedef MemImageViewR<storage_type> view_r_t;
    typedef MemImageViewW<storage_type> view_w_t;
    typedef view_w_t::iter_t iter_t;
    typedef ImageInterpolator<Interpolation::nearest_neighbour, view_r_t> interp_t;
    typedef ImageTransform<interp_t, view_w_t> transform_t;

    buffer_t img_buf(100, 100);

    channel_storage_t* buf = static_cast<channel_storage_t*>(img_buf.data());
    buf[0] = 65535;
    buf[10000] = 32767;
    buf[20000] = 16383;

    view_w_t phtr_mem_view_w(buf, 100, 100);

    phtr_mem_view_w.write_px_val_r(50, 50, 1.0);
    phtr_mem_view_w.write_px_val_g(50, 50, 0.7);
    phtr_mem_view_w.write_px_val_b(50, 50, 0.5);

    std::auto_ptr<iter_t> phtr_iter(phtr_mem_view_w.get_iter(50, 50));

    phtr_iter->inc_pos();
    phtr_iter->write_px_val_r(0.1);
    phtr_iter->write_px_val_g(0.2);
    phtr_iter->write_px_val_b(0.3);

    view_r_t phtr_mem_view(buf, 100, 100);

    vcl_cerr << phtr_mem_view.get_px_val_r(0, 0)
    << " " << phtr_mem_view.get_px_val_g(0, 0)
    << " " << phtr_mem_view.get_px_val_b(0, 0) << vcl_endl;

    vcl_cerr << phtr_mem_view.get_px_val_r(50, 50)
    << " " << phtr_mem_view.get_px_val_g(50, 50)
    << " " << phtr_mem_view.get_px_val_b(50, 50) << vcl_endl;

    vcl_cerr << phtr_mem_view.get_px_val_r(51, 50)
    << " " << phtr_mem_view.get_px_val_g(51, 50)
    << " " << phtr_mem_view.get_px_val_b(51, 50) << vcl_endl;

    interp_t interpolator(phtr_mem_view);
    vcl_cerr << interpolator.get_px_val_r(0.0051, 0.0051)
    << " " << interpolator.get_px_val_g(0.0051, 0.0051)
    << " " << interpolator.get_px_val_b(0.0051, 0.0051) << vcl_endl;

    transform_t img_transform(phtr_mem_view, phtr_mem_view_w);
    img_transform.do_transform();

    //
    // VIL stuff
    //
    typedef vxl_uint_16 vil_channel_t;

    // create image resource for input image
    vcl_cout << "Loading test image."  << vcl_endl;
    vil_image_resource_sptr vil_loaded_img = vil_load_image_resource("test.jpg");
    size_t img_width = vil_loaded_img->ni();
    size_t img_height = vil_loaded_img->nj();

    // now create an image in memory for Photoropter to use
    // as destination buffer
    vil_image_view<vil_channel_t> vil_dst_img(img_width, img_height, 3, 1);
    vil_image_view<vil_channel_t> vil_dst_view(vil_dst_img);

    // create a fitting view on the src buffer and copy the data into it
    vcl_cout << "Copying image to buffer...";
    vcl_cout.flush();
    vil_image_view_base_sptr vil_src_img =
        vil_convert_stretch_range(vil_channel_t(), vil_loaded_img->get_view());
    vil_image_view<vil_channel_t> vil_src_view(vil_src_img);
    vcl_cout << "done."  << vcl_endl;

    vcl_cout << "Transforming...";
    vcl_cout.flush();
    view_r_t phtr_view_r(vil_src_view.memory_chunk().as_pointer(), img_width, img_height);
    view_w_t phtr_view_w(vil_src_view.memory_chunk().as_pointer(), img_width, img_height);

    transform_t phtr_transform(phtr_view_r, phtr_view_w);
    phtr_transform.do_transform();

    vcl_cout << "done."  << vcl_endl;

    vcl_cout << "Saving output image."  << vcl_endl;
    vil_save(vil_dst_view, "out.png");

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
