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