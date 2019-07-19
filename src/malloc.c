#include <zconf.h>
#include "malloc.h"

static void *ft_malloc_page(size_t size, t_header_page *h) {

}

static void *ft_malloc_large(size_t size) {
    void *new_mem = ft_mmap(size);
    size_t i = 0;
    while (i < LEN_LARGES) {
        if (g_state.larges[i].ptr == NULL) {
            g_state.larges[i].ptr = new_mem;
            g_state.larges[i].len = size;
            return new_mem;
        }
        i++;
    }
    return NULL;
}

void *malloc(size_t size) {
    size_t align = ft_align_size(size);

    if (align <= ft_tiny_max_size()) {
        return ft_malloc_page(align, g_state.tiny);
    } else if (align <= ft_small_max_size()) {
        return ft_malloc_page(align, g_state.small);
    } else {
        return ft_malloc_large(align);
    }
}
