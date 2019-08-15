
SRC = src/calloc.c\
    src/free.c\
    src/global_state.c\
    src/malloc.c\
    src/realloc.c\
    src/reallocf.c\
    src/util.c\
    src/util2.c\
    src/util3.c\
    src/valloc.c

FLAGS= -Wall -Wextra -fPIC



# nm malloc.so

# LINUX
# setenv DYLD_LIBRARY_PATH .
# setenv DYLD_INSERT_LIBRARIES malloc.so
# setenv DYLD_FORCE_FLAT_NAMESPACE 1
# export LD_PRELOAD=./libft_malloc.so

# MAC
# export DYLD_LIBRARY_PATH=.
# export DYLD_INSERT_LIBRARIES="libft_malloc.so"
# export DYLD_FORCE_FLAT_NAMESPACE=1

# export LD_PRELOAD=./libft_malloc.so

# /usr/bin/time -l ls


# .h and .so

all:
	gcc -shared -o libft_malloc.so $(FLAGS) $(SRC)

