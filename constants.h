#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stddef.h>
#include <stdbool.h>

extern const size_t HEADER_SIZE;
extern const size_t BUSY_OFFSET;
extern const size_t SIZE_OFFSET;
extern const size_t PREV_OFFSET;

struct Header
{
    bool busy;
    size_t size;
    size_t prev;
};

#endif