#include <stdio.h>
#include "memguard.h"

#define MEMORY_LIMIT (1024 * 1024)  // 1MB limit

void print_memory_status() {
    printf("Current usage: %zu bytes\n", mg_get_usage());
    printf("Memory limit: %zu bytes\n", mg_get_limit());
}

int main() {
    printf("Initializing MemGuard with 1MB limit...\n");
    init_memguard(MEMORY_LIMIT);
    print_memory_status();

    printf("\nAllocating 512KB...\n");
    void* ptr1 = mg_malloc(512 * 1024);
    if (ptr1) {
        printf("Allocation successful.\n");
        print_memory_status();
    } else {
        printf("Allocation failed.\n");
    }

    printf("\nAllocating 256KB...\n");
    void* ptr2 = mg_malloc(256 * 1024);
    if (ptr2) {
        printf("Allocation successful.\n");
        print_memory_status();
    } else {
        printf("Allocation failed.\n");
    }

    printf("\nTrying to allocate 512KB (should fail)...\n");
    void* ptr3 = mg_malloc(512 * 1024);
    if (ptr3) {
        printf("Allocation successful (unexpected).\n");
        print_memory_status();
    } else {
        printf("Allocation failed as expected.\n");
        print_memory_status();
    }

    printf("\nFreeing 512KB...\n");
    mg_free(ptr1);
    print_memory_status();

    printf("\nAllocating 384KB...\n");
    void* ptr4 = mg_malloc(384 * 1024);
    if (ptr4) {
        printf("Allocation successful.\n");
        print_memory_status();
    } else {
        printf("Allocation failed.\n");
    }

    printf("\nCleaning up...\n");
    mg_free(ptr2);
    mg_free(ptr4);
    print_memory_status();

    return 0;
}
