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

    // simple tests
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
    size_t dst_width = img_width;
    size_t dst_height = img_height;
    //size_t dst_width = 150;
    //size_t dst_height = 100;

    // create image buffers
    buffer_t phtr_src_buf(img_width, img_height);
    view_r_t phtr_view_r(phtr_src_buf.data(), img_width, img_height);
    buffer_t phtr_dst_buf(dst_width, dst_height);
    view_w_t phtr_view_w(phtr_dst_buf.data(), dst_width, dst_height);

    // create VIL view for filling and saving the buffers
    vil_image_view<vil_channel_t> vil_src_view
    (static_cast<vil_channel_t*>(phtr_src_buf.data()), img_width, img_height, 3, 1, img_width, img_width * img_height);
    vil_image_view<vil_channel_t> vil_dst_view
    (static_cast<vil_channel_t*>(phtr_dst_buf.data()), dst_width, dst_height, 3, 1, dst_width, dst_width * dst_height);

    // load image, convert and copy data
    vcl_cout << "Copying image to buffer...";
    vcl_cout.flush();
    vil_image_view_base_sptr vil_src_img =
        vil_convert_stretch_range(vil_channel_t(), vil_loaded_img->get_view());
    vil_image_view<vil_channel_t> vil_tmp_view(vil_src_img);
    vcl_cout << "...";
    vcl_cout.flush();
    vil_src_view.deep_copy(vil_tmp_view);
    vcl_cout << "done."  << vcl_endl;

    vcl_cout << "Transforming...";
    vcl_cout.flush();
    transform_t phtr_transform(phtr_view_r, phtr_view_w);
    phtr_transform.do_transform();
    vcl_cout << "done."  << vcl_endl;

    vcl_cout << "Saving output image."  << vcl_endl;
    vil_save(vil_dst_view, "out.png");

    return 0;
}
