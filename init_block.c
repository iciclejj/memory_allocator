#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"
#include "construct_header.h"

void *init_block(size_t size)
{
    void *init_addr = malloc(size);

    // create pointers to each header
    struct Header *start_bound_ptr = init_addr;
    struct Header *useable_ptr = start_bound_ptr + 1;
    struct Header *end_bound_ptr = (char *) init_addr + size - sizeof(struct Header);

    // define start bound optimization
    *(start_bound_ptr) = construct_header(true, 0, 0);

    // define useable block
    size_t useable_size = size - (3 * sizeof(struct Header));
    *(useable_ptr) = construct_header(false, useable_size, 0);

    // define end bound optimization
    *(end_bound_ptr) = construct_header(true, 0, useable_size);

    return useable_ptr;
}