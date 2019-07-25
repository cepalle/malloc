#include <unistd.h>
#include "malloc.h"


static void ft_free_page(t_header *hp, t_header **h) {
	if (*h == NULL || hp == NULL) return;

	if (hp->prev != NULL) {
		hp->prev->next = hp->next;
		if (hp->next != NULL) hp->next->prev = hp->prev;
	} else {
		*h = hp->next;
		if (hp->next != NULL) hp->next->prev = NULL;
	}

	munmap(hp, hp->size + sizeof(t_header));
}

static void ft_free_data(t_header *hd, t_header **h) {
	if (*h == NULL || hd == NULL || hd->is_free) return;

	hd->is_free = TRUE;

	if (hd->next != NULL && hd->next->is_free) {
		hd->size = hd->size + hd->next->size + sizeof(t_header);
		hd->next = hd->next->next;
		if (hd->next != NULL) hd->next->prev = hd;

		if (hd->prev == NULL && hd->next == NULL) {
			ft_free_page(hd - 1, h);
			return;
		}
	}

	if (hd->prev != NULL && hd->prev->is_free) {
		hd->prev->size = hd->prev->size + hd->size + sizeof(t_header);
		hd->prev->next = hd->next;
		if (hd->next != NULL) hd->next->prev = hd->prev;

		if (hd->prev->prev == NULL && hd->prev->next == NULL) {
			ft_free_page(hd->prev - 1, h);
			return;
		}
	}

}

void free(void *ptr) {
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
		ft_free_page(
				hdop,
				&(g_state.large)
		);
	} else if (hdop->enum_page_size == ENUM_PAGE_SIZE_SMALL) {
		ft_free_data(
				hdop,
				&(g_state.small)
		);
	} else {
		ft_free_data(
				hdop,
				&(g_state.tiny)
		);
	}

	// pthread_mutex_unlock(&lock);
}
