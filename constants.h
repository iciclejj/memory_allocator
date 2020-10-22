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

struct Arena
{
    void *address;
    size_t size;
};

#endif