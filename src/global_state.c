#include "malloc.h"


t_malloc_root g_state = {
        NULL,
        NULL,
        NULL
};

bool state_need_init() {
    return g_state.tiny == NULL && g_state.small == NULL && g_state.large == NULL;
}
