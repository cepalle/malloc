#include <zconf.h>
#include "malloc.h"

static void *malloc_page(size_t size, t_header_page *h) {

}

static void *malloc_large(size_t size, t_header_page *large) {

}

void *malloc(size_t size) {
    size_t align = align_size(size);

    if (align <= tiny_max_size()) {
        return malloc_page(align, g_state.tiny);
    } else if (align <= small_max_size()) {
        return malloc_page(align, g_state.small);
    } else {
        void *new_mem = ft_mmap(align);
        size_t i = 0;
        while (i < LEN_LARGES) {
            if (g_state.larges[i].ptr == NULL) {
                g_state.larges[i].ptr = new_mem;
                g_state.larges[i].len = align;
                return new_mem;
            }
            i++;
        }
    }
}
