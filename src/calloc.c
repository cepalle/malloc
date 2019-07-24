#include "malloc.h"


void *calloc(size_t count, size_t size) {
	t_header *mem = malloc(size * count);
	if (mem == NULL) return NULL;

	ft_bzero(mem, (mem - 1)->size);
	return mem;
}
