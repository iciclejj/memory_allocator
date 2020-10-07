#include "constants.h"

struct Header *get_next_header(struct Header *header)
{
    header = (char *)header + header->size + sizeof(struct Header);
    return header;
}

struct Header *get_prev_header(struct Header *header)
{
    header = (char *)header - header->prev - sizeof(struct Header);
    return header;
}

bool is_edge_header(struct Header *header)
{
    if (header->busy == true && header->size == 0)
        return true;
    else
        return false;
}

bool allocate_segment(size_t req_size, struct Header *header)
{
    if (header->size >= req_size)
    {
        // split into two segments if enough space; else allocate entire
        if (header->size > req_size + sizeof(struct Header))
        {
            // initialize succeeding header
            struct Header *next_header = (char *)header + req_size +
                                         sizeof(struct Header);
            next_header->busy = false;
            next_header->size = header->size - req_size - sizeof(struct Header);
            next_header->prev = req_size;

            // readjust header size
            header->size = req_size;
        }
        
        header->busy = true;

        return true;
    }
    else
    {
        return false;
    }
}