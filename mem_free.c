#include <stddef.h>

#include "constants.h"
#include "header_navigation.h"

void mem_free(void *addr)
{
    struct Header *curr_header = addr;
    struct Header *prev_header = get_prev_header(curr_header);
    struct Header *next_header = get_next_header(curr_header);

    curr_header->busy = false;

    // merge next and/or previous segments if also free
    if (next_header->busy == false)
    {
        curr_header->size += next_header->size + sizeof(struct Header);
    }
    if (prev_header->busy == false)
    {
        prev_header->size += curr_header->size + sizeof(struct Header);
    }
}