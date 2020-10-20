#include "allocation.h"
#include "constants.h"
#include "tester.h"

int main() {
    void *test = init_block(1024);

    if (test != NULL) {
        tester(test);
    }

    // create init_addr array and remove need to pass around init_addr

    return 0;
}