/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:50:29 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:50:31 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

static void		ft_free_page(t_header *hp, t_header **h)
{
	if (*h == NULL || hp == NULL)
		return ;
	if (hp->prev != NULL)
	{
		hp->prev->next = hp->next;
		if (hp->next != NULL)
			hp->next->prev = hp->prev;
	}
	else
	{
		*h = hp->next;
		if (hp->next != NULL)
			hp->next->prev = NULL;
	}
	munmap(hp, hp->size + sizeof(t_header));
}

static void		ft_free_data(t_header *hd, t_header **h)
{
	if (*h == NULL || hd == NULL || hd->is_free)
		return ;
	hd->is_free = TRUE;
	if (hd->next != NULL && hd->next->is_free)
	{
		hd->size = hd->size + hd->next->size + sizeof(t_header);
		hd->next = hd->next->next;
		(hd->next != NULL) && (hd->next->prev = hd);
		if (hd->prev == NULL && hd->next == NULL)
		{
			ft_free_page(hd - 1, h);
			return ;
		}
	}
	if (hd->prev != NULL && hd->prev->is_free)
	{
		hd->prev->size = hd->prev->size + hd->size + sizeof(t_header);
		hd->prev->next = hd->next;
		(hd->next != NULL) && (hd->next->prev = hd->prev);
		if (hd->prev->prev == NULL && hd->prev->next == NULL)
		{
			ft_free_page(hd->prev - 1, h);
			return ;
		}
	}
}

t_bool			ft_is_in_headers(void *ptr, t_header *h)
{
	if (h == NULL)
		return (FALSE);
	if (h + 1 == ptr)
		return (TRUE);
	return (ft_is_in_headers(ptr, h->next));
}

t_bool			ft_is_in_page(void *ptr, t_header *h)
{
	if (h == NULL)
		return (FALSE);
	if (ft_is_in_headers(ptr, h + 1))
		return (TRUE);
	return (ft_is_in_page(ptr, h->next));
}

void			free(void *ptr)
{
	t_header *hdop;

	hdop = ptr;
	if (ptr == NULL)
		return ;
	if (ft_is_in_headers(ptr, g_state.large))
	{
		ft_free_page(hdop - 1, &(g_state.large));
	}
	else if (ft_is_in_page(ptr, g_state.small))
	{
		ft_free_data(hdop - 1, &(g_state.small));
	}
	else if (ft_is_in_page(ptr, g_state.tiny))
	{
		ft_free_data(hdop - 1, &(g_state.tiny));
	}
}
