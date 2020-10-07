#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "mem_alloc.h"
#include "constants.h"

void tester(int *init_addr)
{
    int *curr_addr = init_addr;
    srand(time(NULL));

    while (1)
    {
        printf("address: %p\nbusy: %d\nsize: %d\nprev_size: %d\n\n",
                curr_addr,
                *(curr_addr + BUSY_OFFSET),
                *(curr_addr + SIZE_OFFSET),
                *(curr_addr + PREV_OFFSET));

        curr_addr = mem_alloc(rand() % 128 + 1, init_addr);

        if (curr_addr == NULL) {
            break;
        }
        
        curr_addr -= HEADER_SIZE;
    }
}