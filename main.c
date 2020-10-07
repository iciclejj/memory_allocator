#include "init_block.h"
#include "mem_alloc.h"
#include "constants.h"
#include "tester.h"

int main() {
    void *test = init_block(1024);

    tester(test);

    return 0;
}