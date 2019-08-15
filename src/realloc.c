/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:50:53 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:50:54 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

static void	*realloc_aux(t_header *hd, void *ptr, size_t size)
{
	t_header *new_mem;

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

void		*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	return (realloc_aux(((t_header *)ptr) - 1, ptr, size));
}
