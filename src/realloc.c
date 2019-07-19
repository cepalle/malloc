#include "malloc.h"


void *realloc(void *ptr, size_t size) {
    if (ptr == NULL) return malloc(size);

    t_header_data *pi = ptr;
    pi--;

    if (pi->size == size) return ptr;

    void *new_mem = malloc(size);
    if (new_mem == NULL) return NULL;

    ft_memmove(new_mem, pi + 1, ft_min(pi->size, size));
    return new_mem;
}
