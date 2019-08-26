/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:50:44 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:50:45 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <zconf.h>
#include "malloc.h"

static void	*ft_malloc_large_page(size_t size)
{
	size_t		align;
	t_header	*new_mem;

	align = ft_align_size(size + sizeof(t_header), getpagesize());
	new_mem = ft_mmap(align);
	if (new_mem == NULL)
		return (NULL);
	new_mem->next = NULL;
	new_mem->prev = NULL;
	new_mem->size = align - sizeof(t_header);
	new_mem->is_free = FALSE;
	new_mem->enum_page_size = ENUM_PAGE_SIZE_LARGE;
	return (new_mem);
}

static void	*ft_malloc_large(size_t size, t_header **h)
{
	t_header *new_page;
	t_header *it;

	new_page = ft_malloc_large_page(size);
	if (new_page == NULL)
		return (NULL);
	if (*h == NULL)
	{
		*h = new_page;
	}
	else
	{
		it = *h;
		while (it->next != NULL)
		{
			it = it->next;
		}
		it->next = new_page;
		new_page->prev = it;
	}
	return (new_page + 1);
}

void		*malloc(size_t size)
{
	void *res;

	if (size <= PAGE_TINY_DATA_SIZE)
	{
		res = ft_malloc_tiny(
				ft_align_size(size, PAGE_TINY_RES), &(g_state.tiny));
	}
	else if (size <= PAGE_SMALL_DATA_SIZE)
	{
		res = ft_malloc_small(
				ft_align_size(size, PAGE_SMALL_RES), &(g_state.small));
	}
	else
	{
		res = ft_malloc_large(size, &(g_state.large));
	}
	return (res);
}
