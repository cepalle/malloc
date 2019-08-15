#ifndef MALLOC_MALLOC_H
# define MALLOC_MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>

# define PAGE_TINY_SIZE         (1024 * 1024 * 2)
# define PAGE_TINY_RES          16
# define PAGE_TINY_DATA_SIZE    (1024 - sizeof(t_header) - PAGE_TINY_RES + 1)

# define PAGE_SMALL_SIZE        (4096 * 4096)
# define PAGE_SMALL_RES         512
# define PAGE_SMALL_DATA_SIZE   (4096 * 2 - sizeof(t_header) - PAGE_SMALL_RES + 1)

# define ENUM_PAGE_SIZE_TINY    0
# define ENUM_PAGE_SIZE_SMALL   1
# define ENUM_PAGE_SIZE_LARGE   2

# define FALSE                  0
# define TRUE                   1

typedef unsigned char			t_bool;

typedef struct s_mem_large		t_mem_large;

struct							s_header
{
	struct s_header				*next;
	struct s_header				*prev;
	size_t						size;
	t_bool						is_free;
	unsigned char				enum_page_size;
};

typedef struct s_header			t_header;

struct							s_malloc_root
{
	t_header					*tiny;
	t_header					*small;
	t_header					*large;
};

typedef struct s_malloc_root	t_malloc_root;

typedef struct s_header_data	t_header_data;

extern t_malloc_root			g_state;

void		free(void *ptr);

void		*malloc(size_t size);

void		*realloc(void *ptr, size_t size);

void		*calloc(size_t count, size_t size);

void		*reallocf(void *ptr, size_t size);

void		*valloc(size_t size);

void		show_alloc_mem();

size_t		ft_align_size(size_t n, size_t al);

size_t		ft_tiny_max_size();

size_t		ft_small_max_size();

void		ft_bzero(void *ptr, size_t len);

size_t		ft_min(size_t a, size_t b);

size_t		ft_max(size_t a, size_t b);

void		*ft_memmove(void *dst, const void *src, size_t len);

void		*ft_mmap(size_t size);

void		*ft_move_ptr(void *ptr, size_t len);

void		ft_putnbr_fd(int n, int fd);

void		ft_putstr(char const *s);

void		ft_putnbr(int n);

void		ft_putnbr_hex(size_t n);

#endif
