#include <unistd.h>
#include "malloc.h"


static void ft_free_page(t_header *hp, t_header **h) {
	write(1, "FREE_PAGE\n", 10);

	if (*h == NULL || hp == NULL) return;

	if (hp->prev != NULL) {
		hp->prev->next = hp->next;
	} else {
		*h = hp->next;
	}

	munmap(hp, hp->size + sizeof(t_header));
}

static void ft_free_data(t_header *hd, t_header **h) {
	write(1, "FREE_DATA\n", 10);

	if (*h == NULL || hd == NULL || hd->is_free) return;

	hd->is_free = TRUE;
	if (hd->next != NULL && hd->next->is_free == TRUE) {
		hd->size = hd->size + hd->next->size + sizeof(t_header);
		hd->next = hd->next->next;

		if (hd->prev == NULL && hd->next == NULL) {
			ft_free_page(hd - 1, h);
			return;
		}
	}

	if (hd->prev != NULL && hd->prev->is_free) {
		hd->prev->size = hd->prev->size + hd->size + sizeof(t_header);
		hd->prev->next = hd->next;

		if (hd->prev->prev == NULL && hd->prev->next == NULL) {
			ft_free_page(hd->prev - 1, h);
			return;
		}
	}

}

void free(void *ptr) {
	write(1, "FREE\n", 5);
	/*
	if (mutex_need_init) {
		mutex_need_init = pthread_mutex_init(&lock, NULL);
	}
	pthread_mutex_lock(&lock);
	*/
	if (ptr == NULL) return;

	t_header *hdop = ptr;
	hdop--;

	if (hdop->enum_page_size == ENUM_PAGE_SIZE_LARGE) {
		write(1, "FREE_LARGE\n", 11);
		ft_free_page(
				hdop,
				&(g_state.large)
		);
	} else if (hdop->enum_page_size == ENUM_PAGE_SIZE_SMALL) {
		write(1, "FREE_SMALL\n", 11);
		ft_free_data(
				hdop,
				&(g_state.small)
		);
	} else {
		write(1, "FREE_TINY\n", 10);
		ft_free_data(
				hdop,
				&(g_state.tiny)
		);
	}

	// pthread_mutex_unlock(&lock);
}
