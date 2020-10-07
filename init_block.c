#include <stdlib.h>
#include <stdbool.h>

#include "constants.h"

void *init_block(size_t size)
{
    int *start_addr = malloc(size);

   // create start bound optimization
    *(start_addr + BUSY_OFFSET) = true;
    *(start_addr + SIZE_OFFSET) = 0;
    *(start_addr + PREV_OFFSET) = 0;

    // initialize useable space
    int *init_header = start_addr + HEADER_SIZE;
    *(init_header + BUSY_OFFSET) = false;
    *(init_header + SIZE_OFFSET) = size - (3 * HEADER_SIZE);
    *(init_header + PREV_OFFSET) = 0;

    // create end bound optimization
    int *end_header = start_addr + size - HEADER_SIZE;
    *(end_header + BUSY_OFFSET) = true;
    *(end_header + SIZE_OFFSET) = 0;
    *(end_header + PREV_OFFSET) = 0;

    return init_header;
}