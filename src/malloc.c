#include <zconf.h>
#include "malloc.h"

static void *malloc_page(size_t size, t_header_page *h) {

}

static void *malloc_large(size_t size, t_header_page *large) {

}

void *malloc(size_t size) {
    size_t align = align_size(size);

    if (size <= tiny_max_size()) {
        return malloc_page(align, g_state.tiny);
    } else if (size <= small_max_size()) {
        return malloc_page(align, g_state.small);
    } else {



    }
}
