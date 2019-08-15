/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:50:22 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:50:24 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	t_header *mem;

	mem = malloc(size * count);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, (mem - 1)->size);
	return (mem);
}
