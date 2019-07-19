#include <zconf.h>
#include "malloc.h"


static void *malloc_tiny(size_t size, t_header_page *tiny) {

}

static void *malloc_small(size_t size, t_header_page *small) {

}

static void *malloc_large(size_t size, t_header_page *large) {

}

void *malloc(size_t size) {
    size_t align = align_size(size);

    if (size <= tiny_max_size()) {
        return malloc_tiny(align, g_state.tiny);
    } else if (size <= small_max_size()) {
        return malloc_small(align, g_state.small);
    } else {
        return malloc_large(align, g_state.large);
    }
}
