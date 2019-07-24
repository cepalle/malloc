#include <unistd.h>
#include "malloc.h"


void *valloc(size_t size) {
	// write(1, "VALLOC\n", 7);

	return malloc(size);
}
