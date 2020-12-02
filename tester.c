#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "allocator.h"
#include "structures.h"

void tester(void *init_addr)
{
    struct Header *curr_addr = init_addr;
    srand(time(NULL));

    while (1)
    {
        printf("address: %p\nbusy: %d\nsize: %zu\nprev_size: %zu\n\n",
                curr_addr,
                curr_addr->busy,
                curr_addr->size,
                curr_addr->prev);

        curr_addr = mem_alloc(rand() % 128 + 1);

        if (curr_addr == NULL) {
            break;
        }
        --curr_addr; // because mem_alloc returns pointer to the address immediately after the header
    }
}