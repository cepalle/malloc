#ifndef MALLOC_MALLOC_H
#define MALLOC_MALLOC_H

#include <stdlib.h>
#include <sys/mman.h>

/*
mmap
munmap
getpagesize
getrlimit
*/

// TODO
#define PAGE_TINY_SIZE (getpagesize() * getpagesize() / 128)
#define PAGE_SMALL_SIZE (getpagesize() * getpagesize())
#define LEN_LARGES 4096

typedef char t_bool;

struct s_mem_large {
    void *ptr;
    size_t len;
};

typedef struct s_mem_large t_mem_large;

struct s_header_page {
    struct s_header_page *prev;
    struct s_header_page *next;
    size_t size;
};

typedef struct s_header_page t_header_page;

struct s_malloc_root {
    t_header_page *tiny;
    t_header_page *small;
    t_mem_large larges[LEN_LARGES];
};

typedef struct s_malloc_root t_malloc_root;

struct s_header_data {
    struct s_header_data *prev;
    struct s_header_data *next;
    size_t size:63;
    char is_free:1;
};

typedef struct s_header_data t_header_data;

extern t_malloc_root g_state;

// ---

void free(void *ptr);

void *malloc(size_t size);

void *realloc(void *ptr, size_t size);

void *calloc(size_t count, size_t size);

void *reallocf(void *ptr, size_t size);

void *valloc(size_t size);

void show_alloc_mem();

// --- UTIL

size_t ft_align_size(size_t n);

size_t ft_tiny_max_size();

size_t ft_small_max_size();

void ft_bzero(void *ptr, size_t len);

size_t ft_min(size_t a, size_t b);

size_t ft_max(size_t a, size_t b);

void *ft_memmove(void *dst, const void *src, size_t len);

void *ft_mmap(size_t size);

#endif //MALLOC_MALLOC_H
