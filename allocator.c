#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "allocator.h"
#include "structures.h"
#include "allocator_tools.h"

#define ARENAS 32
static struct Arena arena[ARENAS] = {{0}};

void *mem_alloc(size_t req_size)
{
    size_t curr_arena = 0;

    while (curr_arena < ARENAS) 
    {
        // create new arena of size getpagesize() if necessary
        if (arena[curr_arena].address == NULL) {
            size_t pagesize = getpagesize();
            if (req_size <= pagesize - 3 * sizeof(struct Header)) {
                init_block(pagesize);
                continue;
            }
            else {
                return NULL;
            }
        }

        struct Header *curr_header = arena[curr_arena].address;
        ++curr_header; // skip start bound header

        while (!is_edge_header(curr_header))
        {
            if (curr_header->busy == false) {
                if (allocate_segment(req_size, curr_header)) { 
                    return curr_header + 1;
                }
            }
            curr_header = get_next_header(curr_header);
        }

        ++curr_arena;
    }

    return NULL;
}

void *mem_realloc(size_t req_size, void *addr)
{
    struct Header *new_addr = mem_alloc(req_size);

    if (new_addr != NULL) {
        copy_segment(addr, new_addr);
        mem_free(addr);
    }
    
    return new_addr;
}

void mem_free(void *addr)
{
    struct Header *curr_header = addr;
    struct Header *prev_header = get_prev_header(curr_header);
    struct Header *next_header = get_next_header(curr_header);
    struct Header *next_next_header = get_next_header(next_header);

    curr_header->busy = false;

    // merge next and/or previous segments if also free
    if (next_header->busy == false) {
        curr_header->size += next_header->size + sizeof(struct Header);
        next_next_header->prev = curr_header->size;
    }
    if (prev_header->busy == false) {
        prev_header->size += curr_header->size + sizeof(struct Header);
        next_next_header->prev = prev_header->size;
    }
}

void *init_block(size_t req_size)
{
    // use page size if req_size == 0
    if (req_size == 0) {
        req_size = (size_t)getpagesize();
    }

    void *init_addr = malloc(req_size);

    if (init_addr == NULL) {
        return NULL;
    }
    else {
        // initialize new arena
        size_t arena_number = 0;
        while (arena[arena_number].address != NULL) {
            ++arena_number;
        }
        arena[arena_number].address = init_addr;
        arena[arena_number].size = req_size;

        // create pointers to each header
        struct Header *start_bound_ptr = init_addr;
        struct Header *useable_ptr = start_bound_ptr + 1;
        struct Header *end_bound_ptr = (struct Header *)((char *) init_addr +
                                       req_size - sizeof(struct Header));

        // define start bound optimization
        start_bound_ptr->busy = true;
        start_bound_ptr->size = 0;
        start_bound_ptr->prev = 0;

        // define useable block
        size_t useable_size = req_size - (3 * sizeof(struct Header));
        useable_ptr->busy = false;
        useable_ptr->size = useable_size;
        useable_ptr->prev = 0;

        // define end bound optimization
        end_bound_ptr->busy = true;
        end_bound_ptr->size = 0;
        end_bound_ptr->prev = useable_size;

        return init_addr;
    }
}

void mem_dump(void)
{
    size_t curr_arena = 0;

    while (arena[curr_arena].address != NULL) {
        struct Header *curr_header = arena[curr_arena].address;
        printf("--- ARENA %zu ---\n\n", curr_arena);
        do {
            printf("address: %p\nbusy: %d\nsize: %zu\nprev: %zu\n\n",
                    curr_header, curr_header->busy, curr_header->size, curr_header->prev);
            curr_header = get_next_header(curr_header);
        } while (!is_edge_header(curr_header));
        // print omitted edge header 
        printf("address: %p\nbusy: %d\nsize: %zu\nprev: %zu\n\n",
                curr_header, curr_header->busy, curr_header->size, curr_header->prev);

        ++curr_arena;
    }
}