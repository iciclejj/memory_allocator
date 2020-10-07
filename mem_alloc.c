#include <stddef.h>
#include <stdbool.h>

#include "constants.h"

void *mem_alloc(size_t req_size, int *init_addr)
{
    int *curr_addr = init_addr;

    // loop until you reach the end bound or until break
    while (!(*(curr_addr + BUSY_OFFSET) == true &&
             *(curr_addr + SIZE_OFFSET) == 0))
    {
        // check if currently checked segment is free and is big enough
        if (*(curr_addr + BUSY_OFFSET) == false &&
            *(curr_addr + SIZE_OFFSET) >= req_size)
        {
            // split into two segments if enough space
            // else allocate entire segment
            if (*(curr_addr + SIZE_OFFSET) > req_size + HEADER_SIZE)
            {
                // init succeeding segment
                int *next_addr = curr_addr + HEADER_SIZE + req_size;
                *(next_addr + BUSY_OFFSET) = false;
                *(next_addr + SIZE_OFFSET) = *(curr_addr + SIZE_OFFSET) - req_size - HEADER_SIZE;
                *(next_addr + PREV_OFFSET) = req_size;

                // readjust size of selected segment
                *(curr_addr + SIZE_OFFSET) = req_size;
            }

            break;
        }

        // get address of next segment to check
        curr_addr += *(curr_addr + SIZE_OFFSET) + HEADER_SIZE;
    }

    // return NULL if busy segment was chosen (end bound header)
    // else set segment as busy and return pointer to the non-header portion
    if (*(curr_addr + BUSY_OFFSET) == true) {
        return NULL;
    }
    else
    {
        *(curr_addr + BUSY_OFFSET) = true;
        return curr_addr + HEADER_SIZE;
    }
}
