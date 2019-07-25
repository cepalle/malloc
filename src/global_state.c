#include "malloc.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
t_bool mutex_need_init = TRUE;

t_malloc_root g_state = {
		NULL,
		NULL,
		NULL,
};

void show_alloc_mem() {

}
