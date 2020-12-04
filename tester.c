#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "allocator.h"
#include "structures.h"

struct a {
    void *addr;
    size_t size;
    unsigned int checksum;
};

#define TEST_LOOPS 10000
#define A_NUM 1000
#define A_MIN_SIZE 1
#define A_MAX_SIZE 200

struct a a[A_NUM];

static int random_range(int min, int max) {
    return rand() % (max - min + 1) + min;
}

static void buf_fill(void *addr, size_t size) {
    char *c = addr;
    
    for (int i = 0; i < size; ++i)
        c[i] = rand();
}

static unsigned int buf_checksum(void *addr, size_t size) {
    char *c = addr;
    unsigned int checksum = 0;

    for (int i = 0; i < size; i++)
        checksum = (checksum << 2) ^ (checksum >> 5) ^ c[i];
    
    return checksum;
}

int tester()
{
    //prepare tester
    srand(time(NULL));
    for (size_t i = 0; i < A_NUM; ++i)
        a[i].addr = NULL;

    // main tester loop
    void *addr;
    size_t idx, size;
    for (size_t i = 0; i < TEST_LOOPS; ++i) {
        idx = random_range(0, A_NUM -1);

        if (a[idx].addr == NULL) {
            // alloc
            size = random_range(A_MIN_SIZE, A_MAX_SIZE);
            addr = mem_alloc(size);           
            if (addr != NULL) {
                a[idx].addr = addr;
                a[idx].size = size;
                buf_fill(addr, size);
                a[idx].checksum = buf_checksum(addr, size);
            }
        } else {
            // check checksum
            if (a[idx].checksum != buf_checksum(a[idx].addr, a[idx].size)) {
                printf("Found wrong checksum\n");
                return -1;
            }

            // 50/50 free vs realloc
            if (rand() & 1) {
                mem_free(a[idx].addr);
                a[idx].addr = NULL;
            } else {
                size = random_range(A_MIN_SIZE, A_MAX_SIZE);
                addr = mem_realloc(size, a[idx].addr);

                if (addr != NULL) {
                    a[idx].addr = addr;
                    a[idx].size = size;
                    buf_fill(addr, size);
                    a[idx].checksum = buf_checksum(addr, size);
                }
            }
        }
    }

    printf("\n\n\nmem_dump AFTER INITIAL TESTING:\n\n");
    mem_dump();

    // final tester loop
    // check/double-check all checksums of busy addressses, then free them
    for (int i = 0; i < A_NUM; ++i) {
        if (a[i].addr != NULL) {
            if (a[i].checksum != buf_checksum(a[i].addr, a[i].size)) {
                printf("Found wrong checksum in final tester\n");
                return -1;
            }

            mem_free(a[i].addr);
        }
    }

    printf("\n\n\nmem_dump AFTER FINAL TESTING (ALL ADDRESSES FREED):\n\n");
    mem_dump();

    return 0;
}