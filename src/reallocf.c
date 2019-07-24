#include <unistd.h>
#include "malloc.h"


void *reallocf(void *ptr, size_t size) {
	write(1, "REALLOCF\n", 9);

    void *new_mem = realloc(ptr, size);
    if (new_mem == NULL) return NULL;

    if (new_mem != ptr) free(ptr);

    return new_mem;
}
