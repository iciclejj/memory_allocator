#include <stddef.h>
#include <stdbool.h>

#include "constants.h"
#include "header_navigation.h"
#include "mem_free.c"
#include "mem_alloc.h"

void *mem_realloc(size_t req_size, void *addr, void *init_addr)
{
    struct Header *new_addr = mem_alloc(req_size, init_addr);

    if (new_addr != NULL)
    {
        copy_segment(addr, new_addr);
        mem_free(addr);
    }
    
    return new_addr;

/*
    struct Header *curr_header = addr;
    struct Header *next_header = get_next_header(curr_header);
    struct Header *prev_header = get_prev_header(curr_header);

    size_t temp_size = curr_header->size;

    // if requested size is smaller than or equal to current
    if (curr_header->size >= req_size)
    {
        allocate_segment(req_size, curr_header);
        mem_free(get_next_header(curr_header)); // this merges surrounding free blocks

        return curr_header + sizeof(struct Header);
    }

    // merge with next segment if free and big enough
    if (next_header->busy == false)
    {
        size_t next_with_header = next_with_header + sizeof(struct Header);
        if (next_with_header + curr_header->size >= req_size)
        {
            allocate_segment(req_size, curr_header);

            return curr_header + sizeof(struct Header);
        }
    }
    // TODO: merge with previous segment
*/
}