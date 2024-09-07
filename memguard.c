// Include necessary header files
#include "memguard.h" // Our custom memory guard header
#include <stdlib.h>   // For malloc and free functions
#include <stdio.h>    // For fprintf function
#include <stddef.h>   // For size_t and ssize_t
#include <stdint.h>   // For uint32_t and SIZE_MAX

// Define a structure to store allocation information
typedef struct {
    size_t size;      // Stores the size of the allocated memory
    uint32_t magic;   // Stores a magic number for validation
} AllocationInfo;

#define MAGIC_NUMBER 0xDEADBEEF  // Define a magic number for memory validation

static size_t memory_limit = 0;   // Stores the maximum allowed memory usage
static size_t current_usage = 0;  // Tracks the current memory usage

// Function to initialize the memory guard
void init_memguard(size_t limit) {
    if (limit == 0 || limit > SIZE_MAX) {  // Check if the limit is valid
        fprintf(stderr, "Invalid memory limit. Must be greater than 0 and not exceed SIZE_MAX.\n");  // Print error message
        return;  // Exit the function if limit is invalid
    }
    memory_limit = limit;  // Set the memory limit
    current_usage = 0;     // Initialize current usage to 0
    fprintf(stdout, "MemGuard initialized with limit of %zu bytes.\n", memory_limit);  // Print initialization message
}

// Custom malloc function that tracks memory usage
void* mg_malloc(size_t size) {
    // Check if allocating this memory would exceed the limit
    if (current_usage + size + sizeof(AllocationInfo) > memory_limit) {  // Check if allocation exceeds limit
        fprintf(stderr, "Memory allocation of %zu bytes exceeds the limit.\n", size);  // Print error message
        return NULL;  // Return NULL if allocation fails
    }
    
    AllocationInfo* info = malloc(size + sizeof(AllocationInfo));  // Allocate memory for data and AllocationInfo
    if (info) {  // If allocation is successful
        info->size = size;  // Store the requested size
        info->magic = MAGIC_NUMBER;  // Set the magic number
        current_usage += size + sizeof(AllocationInfo);  // Update current usage
        fprintf(stderr, "DEBUG: Allocated %zu bytes at address %p\n", size, (void*)(info + 1));  // Print debug info
        return (void*)(info + 1);  // Return pointer to the allocated memory (after AllocationInfo)
    } else {  // If allocation fails
        fprintf(stderr, "Memory allocation of %zu bytes failed.\n", size);  // Print error message
        return NULL;  // Return NULL
    }
}

// Custom free function that updates memory usage
void mg_free(void* ptr) {
    if (ptr) {  // If pointer is not NULL
        AllocationInfo* info = (AllocationInfo*)ptr - 1;  // Get pointer to AllocationInfo
        fprintf(stderr, "DEBUG: Attempting to free memory at address %p\n", (void*)info);  // Print debug info
        
        if (info->magic == MAGIC_NUMBER) {  // Check if magic number is valid
            current_usage -= info->size + sizeof(AllocationInfo);  // Update current usage
            info->magic = 0;  // Invalidate the magic number
            free(info);  // Free the memory
            fprintf(stderr, "DEBUG: Freed %zu bytes\n", info->size);  // Print debug info
        } else {  // If magic number is invalid
            fprintf(stderr, "Error: Attempt to free invalid memory address %p\n", (void*)info);  // Print error message
        }
    }
}

// Function to get current memory usage
size_t mg_get_usage(void) {
    return current_usage;  // Return the current memory usage
}

// Function to get the set memory limit
size_t mg_get_limit(void) {
    return memory_limit;  // Return the memory limit
}
