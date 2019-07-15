#include <zconf.h>
#include "malloc.h"


void *malloc(size_t size) {
    size_t align = align_size(size);

    if (size <= tiny_max_size()) {

    } else if (size <= small_max_size()) {

    } else {

    }
}
