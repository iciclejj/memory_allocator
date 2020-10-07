#include <stdbool.h>
#include <stddef.h>

#include "constants.h"

struct Header construct_header(bool busy, size_t size, size_t prev) {
    struct Header header = {busy, size, prev};

    return header;
}