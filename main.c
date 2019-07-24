#include "src/malloc.h"

int main() {
	size_t i = 0;
	void *tab[100000] = {0};

	while (i < 10000) {
		tab[i] = malloc(i);
		i++;
	}
	i = 0;
	while (i < 10000) {
		free(tab[i]);
		i++;
	}

}