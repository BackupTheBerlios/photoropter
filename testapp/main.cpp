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
#include <ctime>

void simple_test()
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

    phtr_mem_view_w.write_px_val_r(50, 50, 10);
    phtr_mem_view_w.write_px_val_g(50, 50, 7);
    phtr_mem_view_w.write_px_val_b(50, 50, 5);

    iter_t phtr_iter(phtr_mem_view_w.get_iter(50, 50));

    phtr_iter.inc_x();
    phtr_iter.write_px_val_r(10);
    phtr_iter.write_px_val_g(20);
    phtr_iter.write_px_val_b(30);

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

}

void vil_test()
{
    using namespace phtr;

    // typedefs and constants
    const Storage::type storage_type(Storage::rgb_16_inter);

    typedef ImageBuffer<storage_type> buffer_t;
    typedef MemImageViewR<storage_type> view_r_t;
    typedef MemImageViewW<storage_type> view_w_t;
    typedef view_w_t::iter_t iter_t;
    typedef ImageInterpolator<Interpolation::bilinear, view_r_t> interp_t;
    typedef ImageTransform<interp_t, view_w_t, 2> transform_t;

    // the equivalent vil type
    typedef vxl_uint_16 vil_channel_t;

    // create image resource for the input image
    vcl_cout << "Loading test image."  << vcl_endl;
    vil_image_view<vil_rgb<vil_channel_t> > loaded_img =
        vil_convert_to_component_order(
            vil_convert_to_n_planes(
                3, vil_convert_stretch_range(
                    vil_channel_t(), vil_load("test.jpg")
                )
            )
        );

    // set image size
    size_t img_width = loaded_img.ni();
    size_t img_height = loaded_img.nj();
    size_t dst_width = 1.41 * img_width;
    size_t dst_height = 1.41 * img_height;
    //size_t dst_width = 150;
    //size_t dst_height = 100;

    // create image buffers
    vcl_cout << "Creating buffers for Photoropter."  << vcl_endl;

    // input buffer
    buffer_t src_img_buf(img_width, img_height);
    view_r_t src_img_view(src_img_buf.data(), img_width, img_height);
    // output buffer
    buffer_t dst_img_buf(dst_width, dst_height, true);
    view_w_t dst_img_view(dst_img_buf.data(), dst_width, dst_height);

    // VIL views for I/O
    vil_image_view<vil_rgb<vil_channel_t> > vil_src_view
    (static_cast<vil_rgb<vil_channel_t>*>(src_img_buf.data()), img_width, img_height, 1, 1, img_width, 1);
    vil_image_view<vil_rgb<vil_channel_t> > vil_dst_view
    (static_cast<vil_rgb<vil_channel_t>*>(dst_img_buf.data()), dst_width, dst_height, 1, 1, dst_width, 1);

    // load image, convert and copy data
    vcl_cout << "Copying image to buffer." << vcl_endl;
    vil_src_view.deep_copy(loaded_img);

    time_t t0 = time(0);
    vcl_cout << "Transforming." << vcl_endl;
    transform_t transform(src_img_view, dst_img_view);
    transform.do_transform();
    time_t t1 = time(0);

    vcl_cout << "Time taken: " << difftime(t1, t0) << " seconds." << vcl_endl;

    vcl_cout << "Saving output image."  << vcl_endl;
    vil_save(vil_dst_view, "out.png");
}

int main()
{
    simple_test();
    vil_test();

    return 0;
}
