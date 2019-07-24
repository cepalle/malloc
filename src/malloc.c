#include <zconf.h>
#include "malloc.h"

static void *ft_malloc_data(size_t size, t_header_data *d) {

}

static void *ft_malloc(size_t size, t_header *h) {
	t_header *d = h + 1;


}

static void *ft_malloc_large(size_t size) {
	size_t align = ft_align_size(size + sizeof(t_header), 4096);
	t_header *new_mem = ft_mmap(align);
	if (new_mem == NULL) return NULL;

	new_mem->next = NULL;
	new_mem->prev = NULL;
	new_mem->size = align - sizeof(t_header);
	new_mem->is_free = FALSE;
	new_mem->is_page = TRUE;
	new_mem->enum_page_size = ENUM_PAGE_SIZE_LARGE;

	return new_mem;
}

void *malloc(size_t size) {
	if (size <= PAGE_TINY_DATA_SIZE) {
		return ft_malloc(ft_align_size(size, PAGE_TINY_RES), g_state.tiny);
	} else if (size <= PAGE_SMALL_DATA_SIZE) {
		return ft_malloc(ft_align_size(size, PAGE_SMALL_RES), g_state.small);
	} else {
		return ft_malloc_large(size);
	}
}
