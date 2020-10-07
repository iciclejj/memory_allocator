#include "init_block.h"
#include "mem_alloc.h"
#include "constants.h"
#include "tester.h"

int main() {
    void *test = init_block(1024);

    tester(test);

    // double-check sizeof(struct Header)
    // create init_addr array and remove need to pass around init_addr

    return 0;
}