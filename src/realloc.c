#include "malloc.h"


void *realloc(void *ptr, size_t size) {
    size_t align = ft_align_size(size);

    if (ptr == NULL) return malloc(align);

    t_header_data *pi = ptr;
    pi--;

    if (pi->size == align) return ptr;

    void *new_mem = malloc(align);
    if (new_mem == NULL) return NULL;

    ft_memmove(new_mem, pi + 1, ft_min(pi->size, align));
    return new_mem;
}
