#include "malloc.h"


void free_in_header(void *ptr, t_header_page *h) {
    if (h == NULL) return;
}

void free(void *ptr) {
    if (ptr == NULL) return;

    size_t size = 0;

    if (size <= tiny_max_size()) {
        return free_in_header(ptr, g_state.tiny);
    } else if (size <= small_max_size()) {
        return free_in_header(ptr, g_state.small);
    } else {
        return free_in_header(ptr, g_state.large);
    }
}
