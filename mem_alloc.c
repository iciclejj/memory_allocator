#include <stddef.h>
#include <stdbool.h>

#include "constants.h"

void *mem_alloc(size_t req_size, void *init_addr)
{
    struct Header *curr_addr = init_addr;

    // loop until you reach the end bound or until break
    while (!(curr_addr->busy == true &&
             curr_addr->size == 0))
    {
        // check if currently checked segment is free and is big enough
        if (curr_addr->busy == false &&
            curr_addr->size >= req_size)
        {
            // split into two segments if enough space
            // else allocate entire segment
            if (curr_addr->size > req_size + sizeof(struct Header))
            {
                // init succeeding segment
                struct Header *next_addr = (char *)curr_addr + req_size + 
                                           sizeof(struct Header);
                next_addr->busy = false;
                next_addr->size = curr_addr->size - req_size - 
                                  sizeof(struct Header);
                next_addr->prev = req_size;

                // readjust size of selected segment
                curr_addr->size = req_size;
            }

            break;
        }

        // get address of next segment to check
        //curr_addr = *(curr_addr + SIZE_OFFSET) + HEADER_SIZE;
        curr_addr = (char *)curr_addr + curr_addr->size + sizeof(struct Header);
    }

    // return NULL if busy segment was chosen (end bound header)
    // else set segment as busy and return pointer to the non-header portion
    if (curr_addr->busy == true)
    {
        return NULL;
    }
    else
    {
        curr_addr->busy = true;
        return curr_addr + 1;
    }
}
