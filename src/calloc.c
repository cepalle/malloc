#include <unistd.h>
#include "malloc.h"


void *calloc(size_t count, size_t size) {
	void *mem = malloc(size * count);
	if (mem == NULL) return NULL;
	ft_bzero(mem, size * count);
	return mem;
}
