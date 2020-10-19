#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

#include <stddef.h>

void *mem_alloc(size_t, void *);
void *mem_realloc(size_t, void *, void *);
void mem_free(void *);
void *init_block(size_t);

#endif