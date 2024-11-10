#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

extern "C" void* malloc(size_t size) {
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_CREATE_ALIGN_16, size);
}

extern "C" void* realloc(void* ptr, size_t size) {
    return HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_CREATE_ALIGN_16, ptr, size);
}

extern "C" void free(void* ptr) {
    HeapFree(GetProcessHeap(), 0, ptr);
}

extern "C" void* calloc(size_t num, size_t size) {
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_CREATE_ALIGN_16, num * size);
}
