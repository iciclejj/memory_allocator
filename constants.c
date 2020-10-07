#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

const size_t HEADER_SIZE = sizeof(bool) + sizeof(size_t) + sizeof(size_t);
const size_t BUSY_OFFSET = 0;
const size_t SIZE_OFFSET = sizeof(bool);
const size_t PREV_OFFSET = sizeof(bool) + sizeof(size_t);