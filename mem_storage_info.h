#ifndef __MEM_STORAGE_INFO_H__
#define __MEM_STORAGE_INFO_H__

#include <limits>

#include "storagetypes.h"
#include "channel_storage.h"
#include "mem_layout.h"

namespace phtr
{

    /**
    * \brief Template providing details on the memory storage of a given
    * image type.
    */
    template <Storage::type T>
    struct MemStorageInfo
    {
        /**
        * \brief The channel storage type (e.g., uint8_t).
        */
        typedef typename ChannelStorage<T>::type channel_storage_t;

        /**
        * \brief The memory layout.
        */
        typedef MemLayout<T> mem_layout_t;

        /**
        * \brief Constructor.
        * \param width The image width.
        * \param height The image height.
        */
        MemStorageInfo(coord_t width, coord_t height)
                : width(width),
                height(height),
                min_val(std::numeric_limits<channel_storage_t>::min()),
                max_val(std::numeric_limits<channel_storage_t>::max()),
                step(mem_layout_t::step(width, height)),
                r_offs(mem_layout_t::r_offs(width, height)),
                g_offs(mem_layout_t::g_offs(width, height)),
                b_offs(mem_layout_t::b_offs(width, height))
        {
        }

        /**
        * \brief The image width.
        */
        const coord_t width;

        /**
        * \brief The image height.
        */
        const coord_t height;

        /**
        * \brief The minimal value a channel can store (e.g. 0 for unsigned types).
        */
        const channel_storage_t min_val;

        /**
        * \brief The maximal value a channel can store (e.g. 255 for uint8_t).
        */
        const channel_storage_t max_val;

        /**
        * \brief The step between pixels, in multiples of the channel
        * storage unit (e.g., 1 for planar images, 3 for interleaved).
        */
        const size_t step;

        /**
        * \brief The offset of the red channel to the current memory position
        (e.g. 0 for RGB).
        */
        const size_t r_offs;

        /**
        * \brief The offset of the blue channel to the current memory
        position (e.g. 1 for RGB interleave, width*height for RGB planar).
        */
        const size_t g_offs;

        /**
        * \brief The offset of the green channel to the current memory
        position (e.g. 2 for RGB interleave, 2*width*height for RGB planar).
        */
        const size_t b_offs;
    }; // template struct MemStorageInfo

} // namespace phtr

#endif // __MEM_STORAGE_INFO_H__
