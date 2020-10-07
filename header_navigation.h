#ifndef HEADER_NAVIGATION_H
#define HEADER_NAVIGATION_H

#include <stdbool.h>

#include "constants.h"

struct Header *get_next_header(struct Header *);
struct Header *get_prev_header(struct Header *);

bool is_edge_header(struct Header *);

bool allocate_segment(size_t, struct Header *);
void move_segment(struct Header *, struct Header *);

#endif