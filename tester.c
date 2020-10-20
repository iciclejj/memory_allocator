#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "allocation.h"
#include "constants.h"

void tester(void *init_addr)
{
    struct Header *curr_addr = init_addr;
    srand(time(NULL));

    while (1)
    {
        printf("address: %p\nbusy: %d\nsize: %ld\nprev_size: %ld\n\n",
                curr_addr,
                curr_addr->busy,
                curr_addr->size,
                curr_addr->prev);

        curr_addr = mem_alloc(rand() % 128 + 1, init_addr);

        if (curr_addr == NULL) {
            break;
        }
        
        --curr_addr; // because mem_alloc returns pointer to the address immediately after the header
    }
}