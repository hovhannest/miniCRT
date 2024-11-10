#include <stdio.h>
#include <stdlib.h>

#define MAX_EXIT_FUNCS 32

// Array to hold the exit function pointers
static void (*exit_functions[MAX_EXIT_FUNCS])(void);
static int exit_func_count = 0;

int atexit(void (*func)(void)) {
    // Ensure we do not exceed the array size
    if (exit_func_count >= MAX_EXIT_FUNCS) {
        return -1; // Error: too many functions
    }

    // Add the function to the list
    exit_functions[exit_func_count++] = func;
    return 0; // Success
}

extern "C" void __cdecl mini_exit(void) {
    // Call all registered functions in reverse order
    for (int i = exit_func_count - 1; i >= 0; i--) {
        exit_functions[i]();
    }
}
