#include "malloc.h"


static void ft_free_page(t_header *pf, t_header **h) {
	if (*h == NULL || pf == NULL) return;

	if (pf->prev != NULL) {
		pf->prev->next = pf->next;
	} else {
		*h = pf->next;
	}

	munmap(pf, pf->size + sizeof(t_header));
}

static void ft_free_data(t_header *hd, t_header **h) {
	if (hd == NULL || hd->is_free) return;

	hd->is_free = TRUE;

	if (hd->next != NULL && hd->next->is_free) {
		hd->next = hd->next->next;
		hd->size = hd->size + hd->next->size + sizeof(t_header);
	}

	if (hd->prev != NULL && hd->prev->is_free) {
		hd->prev->next = hd->next;
		hd->prev->size = hd->size + hd->prev->size + sizeof(t_header);
	}

	if (hd->prev == NULL && hd->next == NULL) {
		ft_free_page(hd - 1, h);
		return;
	}

	if (hd->prev != NULL && hd->prev->prev == NULL && hd->prev->next == NULL) {
		ft_free_page(hd->prev - 1, h);
		return;
	}
}

void free(void *ptr) {
	if (ptr == NULL) return;

	t_header *pi = ptr;
	pi--;

	if (pi->enum_page_size == ENUM_PAGE_SIZE_LARGE) {
		ft_free_page(
				pi,
				&(g_state.large)
		);
	} else if (pi->enum_page_size == ENUM_PAGE_SIZE_SMALL) {
		ft_free_data(
				pi,
				&(g_state.small)
		);
	} else {
		ft_free_data(
				pi,
				&(g_state.tiny)
		);
	}
}
