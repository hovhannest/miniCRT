#pragma once

#include <malloc.h>
#include <stdlib.h>
#include <assert.h>

// Test for custom malloc
void test_malloc() {
    int* ptr = (int*)malloc(sizeof(int) * 10);
    assert(ptr != NULL);  // Check if allocation was successful

    // Verify that memory is zero-initialized
    for (int i = 0; i < 10; ++i) {
        assert(ptr[i] == 0);
    }

    free(ptr);  // Clean up
}

// Test for custom realloc
void test_realloc() {
    int* ptr = (int*)malloc(sizeof(int) * 5);
    assert(ptr != NULL);

    // Verify zero-initialization
    for (int i = 0; i < 5; ++i) {
        assert(ptr[i] == 0);
    }

    // Resize the allocation
    ptr = (int*)realloc(ptr, sizeof(int) * 10);
    assert(ptr != NULL);  // Check if reallocation was successful

    // Verify that the new part of the memory is zero-initialized
    for (int i = 5; i < 10; ++i) {
        assert(ptr[i] == 0);
    }

    free(ptr);  // Clean up
}

// Test for custom free (indirectly tested by other functions)

// Test for custom calloc
void test_calloc() {
    int* ptr = (int*)calloc(10, sizeof(int));
    assert(ptr != NULL);  // Check if allocation was successful

    // Verify zero-initialization
    for (int i = 0; i < 10; ++i) {
        assert(ptr[i] == 0);
    }

    free(ptr);  // Clean up
}