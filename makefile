
SRC = src/calloc.c\
    src/free.c\
    src/global_state.c\
    src/malloc.c\
    src/realloc.c\
    src/reallocf.c\
    src/util.c\
    src/valloc.c

FLAGS= -Wall -Wextra

# nm malloc.so
# setenv DYLD_LIBRARY_PATH .
# setenv DYLD_INSERT_LIBRARIES malloc.so
# setenv DYLD_FORCE_FLAT_NAMESPACE 1


all:
	gcc -shared -o malloc.so $(FLAGS) $(SRC)

