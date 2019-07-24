#include <unistd.h>
#include "malloc.h"


void *realloc(void *ptr, size_t size) {
	// write(1, "REALLOC\n", 8);

	if (ptr == NULL) return malloc(size);

	t_header *hd = ptr;
	hd--;

	if (hd->size >= size) return ptr;

	if (hd->next != NULL && hd->next->is_free) {
		hd->size = hd->size + hd->next->size + sizeof(t_header);
	}

	if (hd->size >= size) return ptr;

	void *new_mem = malloc(size);
	if (new_mem == NULL) return NULL;

	ft_memmove(new_mem, hd + 1, ft_min(hd->size, size));
	return new_mem;
}
