// Include guard to prevent multiple inclusions of this header file
#ifndef MEMGUARD_H
// Define MEMGUARD_H if it's not already defined
#define MEMGUARD_H

#include <stddef.h>  // For size_t

// Initialize the memory guard with a specified limit
void init_memguard(size_t limit);

// Allocate memory with tracking
void* mg_malloc(size_t size);

// Free memory with tracking
// This function is used to deallocate memory previously allocated by mg_malloc
// It updates the internal memory usage tracking to reflect the freed memory
// Parameters:
//   ptr: A pointer to the memory block to be freed
// Note: This function should be used instead of the standard free() function
// to ensure proper memory tracking within the MemGuard system
void mg_free(void* ptr);

// Get current memory usage
size_t mg_get_usage(void);

// Get memory limit
size_t mg_get_limit(void);

#endif // MEMGUARD_H
