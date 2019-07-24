#include <unistd.h>
#include "malloc.h"


static void ft_free_page(t_header *pf, t_header **h) {
	write(1, "FREE_PAGE\n", 10);

	if (*h == NULL || pf == NULL) return;

	if (pf->prev != NULL) {
		pf->prev->next = pf->next;
	} else {
		*h = pf->next;
	}

	munmap(pf, pf->size + sizeof(t_header));
}

static void ft_free_data(t_header *hd, t_header **h) {
	write(1, "FREE_DATA\n", 10);

	if (*h == NULL || hd == NULL || hd->is_free) return;

	hd->is_free = TRUE;
	write(1, "FREE_DATA_0\n", 12);
	ft_putnbr((int) hd->next);
	if (hd->next != NULL && hd->next->is_free == TRUE) {
		write(1, "FREE_DATA_9\n", 12);
		hd->size = hd->size + hd->next->size + sizeof(t_header);
		write(1, "FREE_DATA_8\n", 12);
		hd->next = hd->next->next;
		write(1, "FREE_DATA_7\n", 12);
	}
	write(1, "FREE_DATA_1\n", 12);

	if (hd->prev != NULL && hd->prev->is_free) {
		hd->prev->size = hd->prev->size + hd->size + sizeof(t_header);
		hd->prev->next = hd->next;
	}
	write(1, "FREE_DATA_2\n", 12);

	if (hd->prev == NULL && hd->next == NULL) {
		ft_free_page(hd - 1, h);
		return;
	}
	write(1, "FREE_DATA_3\n", 12);

	if (hd->prev != NULL && hd->prev->prev == NULL && hd->prev->next == NULL) {
		ft_free_page(hd->prev - 1, h);
		return;
	}
}

void free(void *ptr) {
	write(1, "FREE\n", 5);

	if (ptr == NULL) return;

	t_header *hp = ptr;
	hp--;

	if (hp->enum_page_size == ENUM_PAGE_SIZE_LARGE) {
		write(1, "FREE_LARGE\n", 11);
		ft_free_page(
				hp,
				&(g_state.large)
		);
	} else if (hp->enum_page_size == ENUM_PAGE_SIZE_SMALL) {
		write(1, "FREE_SMALL\n", 11);
		ft_free_data(
				hp + 1,
				&(g_state.small)
		);
	} else {
		write(1, "FREE_TINY\n", 10);
		ft_free_data(
				hp + 1,
				&(g_state.tiny)
		);
	}
}
