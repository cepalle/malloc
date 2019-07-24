#include <zconf.h>
#include "malloc.h"


size_t ft_align_size(size_t n, size_t al) {
	if (n % al) {
		return ((n / al) + 1) * al;
	} else {
		return n;
	}
}

// --- LIBFT

void ft_bzero(void *s, size_t n) {
	size_t i;
	unsigned char *ss;

	i = 0;
	ss = (unsigned char *) s;
	while (i < n)
		ss[i++] = 0;
}

void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n) {
	size_t i;
	char *dst_bis;
	char *src_bis;

	dst_bis = (char *) dst;
	src_bis = (char *) src;
	i = 0;
	while (i < n) {
		dst_bis[i] = src_bis[i];
		i++;
	}
	return (dst);
}

static void *ft_memcpy_aux(void *restrict dst, const void *restrict src,
						   size_t n) {
	char *dst_bis;
	char *src_bis;

	dst_bis = (char *) dst;
	src_bis = (char *) src;
	while (n > 0) {
		dst_bis[n - 1] = src_bis[n - 1];
		n--;
	}
	return (dst);
}

void *ft_memmove(void *dst, const void *src, size_t len) {
	if (dst == src)
		return (dst);
	else if (dst < src)
		ft_memcpy(dst, src, len);
	else
		ft_memcpy_aux(dst, src, len);
	return (dst);
}

inline size_t ft_min(size_t a, size_t b) {
	return a < b ? a : b;
}

inline size_t ft_max(size_t a, size_t b) {
	return a > b ? a : b;
}

void *ft_mmap(size_t size) {
	return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

void *ft_move_ptr(void *ptr, size_t len) {
	return ptr + len;
}
