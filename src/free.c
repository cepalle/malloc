#include "malloc.h"


static void ft_free_in_header(void *ptr, t_header *h) {
	if (h == NULL || ptr == NULL) return;


}

void free(void *ptr) {
	if (ptr == NULL) return;

	t_header *pi = ptr;
	pi--;

	if (pi->enum_page_size == ENUM_PAGE_SIZE_LARGE) {
		// TODO
		munmap(pi, pi->size + sizeof(t_header));
	} else if (pi->enum_page_size == ENUM_PAGE_SIZE_SMALL) {
		ft_free_in_header(ptr, g_state.small);
	} else {
		ft_free_in_header(ptr, g_state.tiny);
	}
}
