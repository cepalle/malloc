#include <zconf.h>
#include "malloc.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
t_bool mutex_need_init = TRUE;

t_malloc_root g_state = {
        NULL,
        NULL,
        NULL,
};

static void print_add(void *p) {
    write(1, "0x", 2);
    ft_putnbr_hex((size_t) p);
}

static void print_hd(t_header *hd) {
    t_header *it = hd;

    while (it != NULL) {
        print_add(it + 1);
        write(1, " - ", 3);
        print_add(ft_move_ptr(it, it->size + sizeof(t_header)));
        write(1, " : ", 3);
        ft_putnbr(it->size);
        write(1, " octets\n", 8);

        it = it->next;
    }
}

static void print_hp(t_header *hp) {

    t_header *it = hp;
    while (it != NULL) {
        if (it->enum_page_size == ENUM_PAGE_SIZE_LARGE) {
            write(1, "LARGE : \n", 9);
        } else if (it->enum_page_size == ENUM_PAGE_SIZE_SMALL) {
            write(1, "SMALL : \n", 9);
        } else {
            write(1, "TINY : \n", 8);
        }
        print_add(it);
        write(1, "\n", 1);

        print_hd(it + 1);

        it = hp->next;
    }
}

void show_alloc_mem() {
    print_hp(g_state.tiny);
    print_hp(g_state.small);
    print_hp(g_state.large);
}
