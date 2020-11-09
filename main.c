#include "allocator.h"
#include "structures.h"
#include "tester.h"

int main(void) {
    void *test = init_block(0);

    if (test != NULL) {
        tester(test);
        mem_dump();
    }

    // create init_addr array and remove need to pass around init_addr

    return 0;
}