#ifndef CONSTRUCT_HEADER_H
#define CONSTRUCT_HEADER_H

#include <stdbool.h>
#include <stddef.h>

#include "constants.h"

struct Header construct_header(bool, size_t, size_t);

#endif