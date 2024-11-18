// global overrides of new and delete

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstddef>
#include <cstdint>

namespace
{
    inline void* _new(std::size_t sz)
    {
        if (0 == sz)
            sz = 1;
        return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY | HEAP_CREATE_ALIGN_16, sz);
    }

    inline void _delete(void* p)
    {
        HeapFree(GetProcessHeap(), 0, p);
    }
} // unnamed namespace

void* operator new (std::size_t sz)
{
    return _new(sz);
}

void* operator new[](std::size_t sz)
{
    return _new(sz);
}

void* operator new (std::size_t sz, size_t arg)
{
    return _new(sz);
}

//void* operator new (std::size_t, void* ptr) noexcept 
//{ 
//    return ptr;
//}

//void* operator new[](std::size_t, void* ptr) noexcept 
//{
//    return ptr;  
//}

//void operator delete (void* ptr)
//{
//    _delete(ptr);
//}

void operator delete[](void* ptr)
{
    _delete(ptr);
}

void operator delete (void* ptr, size_t arg)
{
    _delete(ptr);
}

//void operator delete (void*, void*) noexcept {}
//void operator delete[](void*, void*) noexcept {}
