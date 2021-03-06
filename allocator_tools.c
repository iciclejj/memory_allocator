#include "allocator_tools.h"
#include "structures.h"

struct Header *get_next_header(struct Header *header)
{
    header = (struct Header *)((char *)header + header->size + sizeof(struct Header));
    return header;
}

struct Header *get_prev_header(struct Header *header)
{
    header = (struct Header *)((char *)header - header->prev - sizeof(struct Header));
    return header;
}

bool is_edge_header(struct Header *header)
{
    if (header->busy == true && header->size == 0)
        return true;
    else
        return false;
}

// give the passed header a size of at least req_size if its current size is big enough.
// also split into two segments if enough space. the extra segment gets set to busy=false.
// caller is responsible for setting and checking the busy flag of the passed header (not touched by this function);
bool allocate_segment(size_t req_size, struct Header *header)
{
    if (header->size >= req_size && req_size > 0)
    {
        // split into two segments if enough space; else allocate entire
        if (header->size > req_size + sizeof(struct Header))
        {
            // initialize succeeding header
            struct Header *next_header = (struct Header *)((char *)header + req_size +
                                         sizeof(struct Header));
            next_header->busy = false;
            next_header->size = header->size - req_size - sizeof(struct Header);
            next_header->prev = req_size;

            // readjust prev of next next header
            struct Header *next_next_header = get_next_header(next_header);
            next_next_header->prev = next_header->size;

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

void copy_segment(void *origin, void *destination) // expects pointer to useable space
{
    struct Header *origin_header = origin - sizeof(struct Header);
    struct Header *destination_header = destination - sizeof(struct Header);

    size_t total_bytes;

    if (origin_header->size > destination_header->size)
        total_bytes = destination_header->size;
    else
        total_bytes = origin_header->size;

    char *origin_curr = origin;
    char *destination_curr = destination;

    for (size_t byte = 0; byte < total_bytes; ++byte)
        destination_curr[byte] = origin_curr[byte];
}