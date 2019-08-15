/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   util.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:51:05 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:51:07 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <zconf.h>
#include "malloc.h"

static void		ft_putnbr_fd_aux(int n, int fd)
{
	if (n > 9)
		ft_putnbr_fd_aux(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	ft_putnbr_fd_aux(n, fd);
}

void			ft_putnbr_hex(size_t n)
{
	static char *str;

	str = "0123456789ABCDEF";
	if (n > 15)
	{
		ft_putnbr_hex(n / 16);
	}
	write(1, str + (n % 16), 1);
}

void			ft_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
}
