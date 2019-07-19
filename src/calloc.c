#include "malloc.h"


void *calloc(size_t count, size_t size) {
    size_t align = align_size(size * count);

    unsigned char *mem = malloc(align);
    ft_bzero(mem, align);
    return mem;
}
