#include <stddef.h>
#include <stdbool.h>

#include "constants.h"
#include "header_navigation.h"

void *mem_alloc(size_t req_size, void *init_addr)
{
    struct Header *curr_header = init_addr;

    while (!is_edge_header(curr_header)) // rewrite for arena struct
    {
        if (curr_header->busy == false) {
            if (allocate_segment(req_size, curr_header)) { 
                break;
            }
        }
        else
            curr_header = get_next_header(curr_header);
    }

    if (is_edge_header(curr_header))
        // make new arena (return null only when init returns null, aka when arena array is full)
        return NULL;
    else
        return curr_header + 1;
}

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

void *init_block(size_t size)
{
    void *init_addr = malloc(size);

    if (init_addr == NULL) {
        return NULL;
    }

    // create pointers to each header
    struct Header *start_bound_ptr = init_addr;
    struct Header *useable_ptr = start_bound_ptr + 1;
    struct Header *end_bound_ptr = (struct Header *)((char *) init_addr + size - sizeof(struct Header));

    // define start bound optimization
    start_bound_ptr->busy = false;
    start_bound_ptr->size = 0;
    start_bound_ptr->prev = 0;

    // define useable block
    size_t useable_size = size - (3 * sizeof(struct Header));
    useable_ptr->busy = false;
    useable_ptr->size = useable_size;
    useable_ptr->prev = 0;

    // define end bound optimization
    end_bound_ptr->busy = true;
    end_bound_ptr->size = 0;
    end_bound_ptr->prev = useable_size;

    return useable_ptr;
}