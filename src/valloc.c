/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   valloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cepalle <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/15 16:51:12 by cepalle      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/15 16:51:14 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <zconf.h>
#include "malloc.h"

void	*valloc(size_t size)
{
	return (malloc(size));
}
