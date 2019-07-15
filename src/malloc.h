#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

#include <stdlib.h>


/*
mmap
munmap
getpagesize
getrlimit
*/



typedef char bool;


struct s_header_page {
    struct s_header_page *prev;
    struct s_header_page *next;
    struct s_data_payload *data;
    size_t size;
};

typedef struct s_header_page header_page;

struct s_malloc_root {
    header_page *tiny;
    header_page *small;
    header_page *large;
};

typedef struct s_malloc_root malloc_root;

struct s_header_data {
    header_page *prev;
    header_page *next;
    size_t size;
};

typedef struct s_header_data header_data;


extern malloc_root g_state;

// ---

void free(void *ptr);

void *malloc(size_t size);

void *realloc(void *ptr, size_t size);

void *calloc(size_t count, size_t size);

void *reallocf(void *ptr, size_t size);

void *valloc(size_t size);

void show_alloc_mem();

size_t tiny_max_size();

size_t small_max_size();

// ---


size_t align_size(size_t n);


#endif //MALLOC_MALLOC_H
