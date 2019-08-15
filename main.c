#include <zconf.h>
#include "src/malloc.h"

#define NUM 128

int main() {
    size_t i = 0;
    void *tab[NUM] = {0};
    void *tab2[NUM] = {0};

    while (i < NUM) {
        tab[i] = malloc(i);
        tab2[i] = malloc(i + 1024);
        i++;
    }
    i = 0;

    show_alloc_mem();

    while (i < NUM) {
        free(tab[i]);
        free(tab2[i]);
        i++;
    }

    write(1, "---\n", 4);

    show_alloc_mem();
}