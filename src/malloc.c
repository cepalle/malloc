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

static void	*ft_malloc_data_tiny(size_t size, t_header *hp)
{
	t_header *hdi;
	t_header *hdin;

	hdi = hp + 1;
	if (hp == NULL)
		return (NULL);
	while (hdi != NULL)
	{
		if (hdi->is_free && hdi->size >= size)
		{
			if (size + sizeof(t_header) + PAGE_TINY_RES < hdi->size)
			{
				hdin = ft_move_ptr(hdi, sizeof(t_header) + size);
				hdin->next = hdi->next;
				if (hdin->next != NULL)
					hdi->next->prev = hdin;
				hdin->prev = hdi;
				hdin->prev->next = hdin;
				hdin->size = hdi->size - sizeof(t_header) - size;
				hdin->is_free = TRUE;
				hdin->enum_page_size = ENUM_PAGE_SIZE_TINY;
				hdi->size = size;
			}
			hdi->is_free = FALSE;
			return (hdi);
		}
		hdi = hdi->next;
	}
	return (NULL);
}

static void	*ft_malloc_page_tiny(void)
{
	t_header *new_mem;
	t_header *hd;

	new_mem = ft_mmap(PAGE_TINY_SIZE);
	if (new_mem == NULL)
		return (NULL);
	new_mem->next = NULL;
	new_mem->prev = NULL;
	new_mem->size = PAGE_TINY_SIZE - sizeof(t_header);
	new_mem->is_free = FALSE;
	new_mem->enum_page_size = ENUM_PAGE_SIZE_TINY;
	hd = new_mem + 1;
	hd->next = NULL;
	hd->prev = NULL;
	hd->size = new_mem->size - sizeof(t_header);
	hd->is_free = TRUE;
	hd->enum_page_size = ENUM_PAGE_SIZE_TINY;
	return (new_mem);
}

static void	*ft_malloc_tiny(size_t size, t_header **h)
{
	t_header *hpi;
	t_header *hd;

	if (*h == NULL)
		*h = ft_malloc_page_tiny();
	hpi = *h;
	hd = NULL;
	while (1)
	{
		hd = ft_malloc_data_tiny(size, hpi);
		if (hd != NULL)
			return (hd + 1);
		if (hpi->next == NULL)
		{
			hpi->next = ft_malloc_page_tiny();
			if (hpi->next == NULL)
				return (NULL);
			hpi->next->prev = hpi;
		}
		hpi = hpi->next;
	}
}

static void	*ft_malloc_data_small(size_t size, t_header *hp)
{
	t_header *hdi;
	t_header *hdin;

	if (hp == NULL)
		return (NULL);
	hdi = hp + 1;
	while (hdi != NULL)
	{
		if (hdi->is_free && hdi->size >= size)
		{
			if (size + sizeof(t_header) + PAGE_SMALL_RES < hdi->size)
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

static void	*ft_malloc_small(size_t size, t_header **h)
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

static void	*ft_malloc_large_page(size_t size)
{
	size_t		align;
	t_header	*new_mem;

	align = ft_align_size(size + sizeof(t_header), 4096);
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
		it->next->prev = it;
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
