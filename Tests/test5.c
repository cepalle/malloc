/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test5.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/08 16:27:04 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 12:38:32 by cepalle     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>

void show_alloc_mem(void);

int	main(void)
{
	void *a = malloc(1024);
	void *b = malloc(1024 * 32);
	void *c = malloc(1024 * 1024);
	void *d = malloc(1024 * 1024 * 16);
	void *e = malloc(1024 * 1024 * 128);
	show_alloc_mem();
	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	write(1, "\n", 1);
	show_alloc_mem();
	return (0);
}
