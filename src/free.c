#include "malloc.h"


static void ft_free(t_header *ptr, t_header **h) {
	if (h == NULL || ptr == NULL) return;


}

// --- LARGE

static void ft_free_large(t_header *pf, t_header **h) {
	if (*h == NULL) return;

	t_header *it = *h;
	while (it != NULL) {
		if (it == pf) {

			if (it->prev != NULL) {
				it->prev->next = it->next;
			} else {
				*h = it->next;
			}

			munmap(pf, pf->size + sizeof(t_header));
			return;
		}
	}
}

void free(void *ptr) {
	if (ptr == NULL) return;

	t_header *pi = ptr;
	pi--;

	if (pi->enum_page_size == ENUM_PAGE_SIZE_LARGE) {
		ft_free_large(
				pi,
				&(g_state.large)
		);
	} else if (pi->enum_page_size == ENUM_PAGE_SIZE_SMALL) {
		ft_free(
				pi,
				&(g_state.small)
		);
	} else {
		ft_free(
				pi,
				&(g_state.tiny)
		);
	}
}
