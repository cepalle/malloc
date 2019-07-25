#include <unistd.h>
#include "malloc.h"


void *reallocf(void *ptr, size_t size) {
	void *new_mem = realloc(ptr, size);
	if (new_mem != ptr) free(ptr);
	return new_mem;
}
