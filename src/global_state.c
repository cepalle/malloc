/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   global_state.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:50:36 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:50:37 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

t_malloc_root g_state = {NULL, NULL, NULL};

static void		print_add(void *p)
{
	write(1, "0x", 2);
	ft_putnbr_hex((size_t)p);
}

static void		print_hd(t_header *hd)
{
	t_header *it;

	it = hd;
	while (it != NULL)
	{
		if (!it->is_free)
		{
			print_add(it + 1);
			write(1, " - ", 3);
			print_add(ft_move_ptr(it, it->size + sizeof(t_header)));
			write(1, " : ", 3);
			ft_putnbr(it->size);
			write(1, " octets\n", 8);
		}
		it = it->next;
	}
}

static void		print_hp(t_header *hp)
{
	t_header *it;

	it = hp;
	while (it != NULL)
	{
		if (it->enum_page_size == ENUM_PAGE_SIZE_LARGE)
		{
			write(1, "LARGE : ", 8);
		}
		else if (it->enum_page_size == ENUM_PAGE_SIZE_SMALL)
		{
			write(1, "SMALL : ", 8);
		}
		else
		{
			write(1, "TINY : ", 7);
		}
		print_add(it);
		write(1, "\n", 1);
		print_hd(it + 1);
		it = it->next;
	}
}

void			show_alloc_mem(void)
{
	print_hp(g_state.tiny);
	print_hp(g_state.small);
	print_hp(g_state.large);
}
