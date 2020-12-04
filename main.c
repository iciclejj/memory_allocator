#include <stdio.h>
#include <unistd.h>

#include "allocator.h"
#include "structures.h"
#include "tester.h"

int main(void) {
    if (tester() != 0)
        printf("Tester failed\n");
    else 
        printf("No errors found\n");

    return 0;
}