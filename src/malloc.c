#include <zconf.h>
#include "malloc.h"


// --- TINY

static void *ft_malloc_data_tiny(size_t size, t_header *hp) {
	t_header *hdi = hp + 1;

	while (hdi != NULL) {
		if (hdi->is_free && hdi->size >= size) {
			if (size + sizeof(t_header) + PAGE_TINY_RES < hdi->size) {
				t_header *hdin = ft_move_ptr(hdi, sizeof(t_header) + size);

				hdin->next = hdi->next;
				hdin->prev = hdi;
				hdin->size = hdi->size - sizeof(t_header) - size;
				hdin->is_free = TRUE;
				hdin->enum_page_size = ENUM_PAGE_SIZE_TINY;

				hdi->size = size;
				hdi->next = hdin;
			}
			hdi->is_free = FALSE;
			return hdi;

		}
		hdi = hdi->next;
	}
	return NULL;
}

static void *ft_malloc_page_tiny() {
	t_header *new_mem = ft_mmap(PAGE_TINY_SIZE);
	if (new_mem == NULL) return NULL;

	new_mem->next = NULL;
	new_mem->prev = NULL;
	new_mem->size = PAGE_TINY_SIZE - sizeof(t_header);
	new_mem->is_free = FALSE;
	new_mem->enum_page_size = ENUM_PAGE_SIZE_TINY;

	t_header *hd = new_mem + 1;
	hd->next = NULL;
	hd->prev = NULL;
	hd->size = new_mem->size - sizeof(t_header);
	hd->is_free = TRUE;
	hd->enum_page_size = ENUM_PAGE_SIZE_TINY;

	return new_mem;
}

static void *ft_malloc_tiny(size_t size, t_header **h) {
	if (*h == NULL) {
		*h = ft_malloc_page_tiny();
	}

	t_header *hpi = *h;
	t_header *hd = NULL;

	while (1) {
		hd = ft_malloc_data_tiny(size, hpi);
		if (hd != NULL) return hd + 1;

		if (hpi->next == NULL) {
			hpi->next = ft_malloc_page_tiny();
		}
		hpi = hpi->next;
	}
}

// --- SMALL

static void *ft_malloc_data_small(size_t size, t_header *hp) {
	t_header *hdi = hp + 1;

	while (hdi != NULL) {
		if (hdi->is_free && hdi->size >= size) {
			if (size + sizeof(t_header) + PAGE_SMALL_RES < hdi->size) {
				t_header *hdin = ft_move_ptr(hdi, sizeof(t_header) + size);

				hdin->next = hdi->next;
				hdin->prev = hdi;
				hdin->size = hdi->size - sizeof(t_header) - size;
				hdin->is_free = TRUE;
				hdin->enum_page_size = ENUM_PAGE_SIZE_SMALL;

				hdi->size = size;
				hdi->next = hdin;
			}
			hdi->is_free = FALSE;
			return hdi;

		}
		hdi = hdi->next;
	}
	return NULL;
}

static void *ft_malloc_page_small() {
	t_header *new_mem = ft_mmap(PAGE_SMALL_SIZE);
	if (new_mem == NULL) return NULL;

	new_mem->next = NULL;
	new_mem->prev = NULL;
	new_mem->size = PAGE_SMALL_SIZE - sizeof(t_header);
	new_mem->is_free = FALSE;
	new_mem->enum_page_size = ENUM_PAGE_SIZE_SMALL;

	t_header *hd = new_mem + 1;
	hd->next = NULL;
	hd->prev = NULL;
	hd->size = new_mem->size - sizeof(t_header);
	hd->is_free = TRUE;
	hd->enum_page_size = ENUM_PAGE_SIZE_SMALL;

	return new_mem;
}

static void *ft_malloc_small(size_t size, t_header **h) {
	if (*h == NULL) {
		*h = ft_malloc_page_small();
	}

	t_header *hpi = *h;
	t_header *hd = NULL;

	while (1) {
		hd = ft_malloc_data_small(size, hpi);
		if (hd != NULL) return hd + 1;

		if (hpi->next == NULL) {
			hpi->next = ft_malloc_page_small();
		}
		hpi = hpi->next;
	}
}

// --- LARGE

static void *ft_malloc_large_page(size_t size) {
	size_t align = ft_align_size(size + sizeof(t_header), 4096);
	t_header *new_mem = ft_mmap(align);
	if (new_mem == NULL) return NULL;

	new_mem->next = NULL;
	new_mem->prev = NULL;
	new_mem->size = align - sizeof(t_header);
	new_mem->is_free = FALSE;
	new_mem->enum_page_size = ENUM_PAGE_SIZE_LARGE;

	return new_mem;
}

static void *ft_malloc_large(size_t size, t_header **h) {
	t_header *new_page = ft_malloc_large_page(size);
	if (new_page == NULL) return NULL;

	if (*h == NULL) {
		*h = new_page;
	} else {
		t_header *it = *h;
		while (it->next) {
			it = it->next;
		}
		it->next = new_page;
	}

	return new_page + 1;
}

void *malloc(size_t size) {
	// write(1, "MALLOC\n", 7);

	if (size <= PAGE_TINY_DATA_SIZE) {
		return ft_malloc_tiny(
				ft_align_size(size, PAGE_TINY_RES),
				&(g_state.tiny)
		);
	} else if (size <= PAGE_SMALL_DATA_SIZE) {
		return ft_malloc_small(
				ft_align_size(size, PAGE_SMALL_RES),
				&(g_state.small)
		);
	} else {
		return ft_malloc_large(
				size,
				&(g_state.large)
		);
	}
}
