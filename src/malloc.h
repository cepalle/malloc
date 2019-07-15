#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

#include <stdlib.h>


void free(void *ptr);

void *malloc(size_t size);

void *realloc(void *ptr, size_t size);

void *calloc(size_t count, size_t size);

void *reallocf(void *ptr, size_t size);

void *valloc(size_t size);

#endif //MALLOC_MALLOC_H
