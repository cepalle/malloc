#include <zconf.h>
#include "malloc.h"


void *valloc(size_t size) {
	return malloc(size);
}
