#include "init_block.h"
#include "mem_alloc.h"
#include "constants.h"
#include "tester.h"

int main() {
    int *test = init_block(1024);

    tester(test);

    return 0;
}