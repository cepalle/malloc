/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   reallocf.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:50:59 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:51:01 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include "malloc.h"

void	*reallocf(void *ptr, size_t size)
{
	void *new_mem;

	new_mem = realloc(ptr, size);
	if (new_mem != ptr)
		free(ptr);
	return (new_mem);
}
