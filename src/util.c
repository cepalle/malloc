#include <zconf.h>
#include "malloc.h"


size_t align_size(size_t n) {
    if (n % sizeof(int)) {
        return ((n / sizeof(int)) + 1) * sizeof(int);
    } else {
        return n;
    }
}

size_t tiny_max_size() {
    return getpagesize() - sizeof(header_data);
}

size_t small_max_size() {
    return getpagesize() * getpagesize() - sizeof(header_data);
}
