
SRC = src/calloc.c\
    src/free.c\
    src/global_state.c\
    src/malloc.c\
    src/realloc.c\
    src/reallocf.c\
    src/util.c\
    src/valloc.c

FLAGS= -Wall -Wextra

all:
	gcc -shared -o malloc.so $(FLAGS) $(SRC)

