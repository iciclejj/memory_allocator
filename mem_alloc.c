#include <stddef.h>
#include <stdbool.h>

#include "constants.h"
#include "header_navigation.h"

void *mem_alloc(size_t req_size, void *init_addr)
{
    struct Header *curr_header = init_addr;

    while (!is_edge_header(curr_header)) // rewrite for arena struct
    {
        if (allocate_segment(req_size, curr_header))
            break;
        else
            curr_header = get_next_header(curr_header);
    }

    if (is_edge_header(curr_header))
        // make new arena (return null only when init returns null, aka when arena array is full)
        return NULL;
    else
        return curr_header + 1;
}
