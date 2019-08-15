/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   util3.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 17:00:52 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 17:00:53 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <zconf.h>
#include "malloc.h"

inline size_t	ft_min(size_t a, size_t b)
{
	return (a < b ? a : b);
}

inline size_t	ft_max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

void			*ft_mmap(size_t size)
{
	return (mmap(NULL, size, PROT_READ | PROT_WRITE,
	MAP_ANON | MAP_PRIVATE, -1, 0));
}

void			*ft_move_ptr(void *ptr, size_t len)
{
	unsigned char *it;

	it = ptr;
	return (it + len);
}

void			ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
