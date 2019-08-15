#include <unistd.h>
#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_header *hd;
	t_header *new_mem;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	hd = ptr;
	hd--;
	if (hd->size >= size)
		return (ptr);
	if (hd->enum_page_size != ENUM_PAGE_SIZE_LARGE &&
		hd->next != NULL && hd->next->is_free)
	{
		hd->size = hd->size + hd->next->size + sizeof(t_header);
		hd->next = hd->next->next;
		if (hd->next != NULL)
			hd->next->prev = hd;
		if (hd->size >= size)
			return (ptr);
	}
	new_mem = malloc(size);
	if (new_mem == NULL)
		return (NULL);
	ft_memmove(new_mem, ptr, ft_min(hd->size, (new_mem - 1)->size));
	free(ptr);
	return (new_mem);
}
