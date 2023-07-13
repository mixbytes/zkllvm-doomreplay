#include <stdlib.h>
void *malloc(size_t size) {
    return __builtin_assigner_malloc(size);
}
void free(void *ptr) {
    __builtin_assigner_free(ptr);
}

