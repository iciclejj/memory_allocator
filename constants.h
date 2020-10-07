#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stddef.h>
#include <stdbool.h>

struct Header
{
    bool busy;
    size_t size;
    size_t prev;
};

#endif