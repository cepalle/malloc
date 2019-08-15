#include <zconf.h>
#include "malloc.h"

size_t			ft_align_size(size_t n, size_t al)
{
	if (n % al)
		return (((n / al) + 1) * al);
	else
		return (n);
}

void			ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	i = 0;
	ss = (unsigned char *)s;
	while (i < n)
		ss[i++] = 0;
}

void			*ft_memcpy(void *restrict dst,
	const void *restrict src, size_t n)
{
	size_t		i;
	char		*dst_bis;
	char		*src_bis;

	dst_bis = (char *)dst;
	src_bis = (char *)src;
	i = 0;
	while (i < n)
	{
		dst_bis[i] = src_bis[i];
		i++;
	}
	return (dst);
}

static void		*ft_memcpy_aux(void *restrict dst, const void *restrict src,
	size_t n)
{
	char *dst_bis;
	char *src_bis;

	dst_bis = (char *)dst;
	src_bis = (char *)src;
	while (n > 0)
	{
		dst_bis[n - 1] = src_bis[n - 1];
		n--;
	}
	return (dst);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	else if (dst < src)
		ft_memcpy(dst, src, len);
	else
		ft_memcpy_aux(dst, src, len);
	return (dst);
}

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

void			ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void			ft_putstr(char const *s)
{
	ft_putstr_fd(s, 1);
}
