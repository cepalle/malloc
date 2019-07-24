#include "malloc.h"


static void ft_free_in_header(void *ptr, t_header_page *h) {
    if (h == NULL) return;


}

void free(void *ptr) {
    if (ptr == NULL) return;

    size_t i = 0;

    t_header_data *pi = ptr;
    pi--;

    if (pi->size <= ft_tiny_max_size()) {
        ft_free_in_header(ptr, g_state.tiny);
    } else if (pi->size <= ft_small_max_size()) {
        ft_free_in_header(ptr, g_state.small);
    }
}
