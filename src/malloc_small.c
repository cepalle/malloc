/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc_small.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 17:19:52 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 17:19:53 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <zconf.h>
#include "malloc.h"

static void	ft_malloc_data_small_aux(t_header *hdin, t_header *hdi, size_t size)
{
	hdin = ft_move_ptr(hdi, sizeof(t_header) + size);
	hdin->next = hdi->next;
	if (hdin->next != NULL)
		hdi->next->prev = hdin;
	hdin->prev = hdi;
	hdin->prev->next = hdin;
	hdin->size = hdi->size - sizeof(t_header) - size;
	hdin->is_free = TRUE;
	hdin->enum_page_size = ENUM_PAGE_SIZE_SMALL;
	hdi->size = size;
	hdi->next = hdin;
}

static void	*ft_malloc_data_small(size_t size, t_header *hp)
{
	t_header *hdi;
	t_header *hdin;

	hdin = NULL;
	if (hp == NULL)
		return (NULL);
	hdi = hp + 1;
	while (hdi != NULL)
	{
		if (hdi->is_free && hdi->size >= size)
		{
			if (size + sizeof(t_header) + PAGE_SMALL_RES < hdi->size)
			{
				ft_malloc_data_small_aux(hdin, hdi, size);
			}
			hdi->is_free = FALSE;
			return (hdi);
		}
		hdi = hdi->next;
	}
	return (NULL);
}

static void	*ft_malloc_page_small(void)
{
	t_header *new_mem;
	t_header *hd;

	new_mem = ft_mmap(PAGE_SMALL_SIZE);
	if (new_mem == NULL)
		return (NULL);
	new_mem->next = NULL;
	new_mem->prev = NULL;
	new_mem->size = PAGE_SMALL_SIZE - sizeof(t_header);
	new_mem->is_free = FALSE;
	new_mem->enum_page_size = ENUM_PAGE_SIZE_SMALL;
	hd = new_mem + 1;
	hd->next = NULL;
	hd->prev = NULL;
	hd->size = new_mem->size - sizeof(t_header);
	hd->is_free = TRUE;
	hd->enum_page_size = ENUM_PAGE_SIZE_SMALL;
	return (new_mem);
}

void		*ft_malloc_small(size_t size, t_header **h)
{
	t_header *hpi;
	t_header *hd;

	if (*h == NULL)
		*h = ft_malloc_page_small();
	hpi = *h;
	hd = NULL;
	while (1)
	{
		hd = ft_malloc_data_small(size, hpi);
		if (hd != NULL)
			return (hd + 1);
		if (hpi->next == NULL)
		{
			hpi->next = ft_malloc_page_small();
			if (hpi->next == NULL)
				return (NULL);
			hpi->next->prev = hpi;
		}
		hpi = hpi->next;
	}
}
