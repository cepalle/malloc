#include "malloc.h"


size_t align_size(size_t n) {
    if (n % sizeof(int)) {
        return ((n / sizeof(int)) + 1) * sizeof(int)
    } else {
        return n;
    }
}
