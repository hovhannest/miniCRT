#ifdef _M_IX86
#include <stdint.h>

uint64_t _allmul(int64_t value1, int64_t value2) {
    uint64_t result;

    __asm {
        push ebx

        ; Multiply low by high of both components, adding them into a temporary register
        mov eax, dword ptr[value1]
        mov edx, dword ptr[value2 + 4]
        mul edx
        mov ebx, eax

        ; Multiply low by low, which might result in a high component
        mov eax, dword ptr[value1 + 4]
        mov edx, dword ptr[value2]
        mul edx
        add ebx, eax

        ; Add back the temporary result into this high component
        mov eax, dword ptr[value1]
        mov edx, dword ptr[value2 + 4]
        mul edx
        add edx, ebx

        ; Store the result
        mov dword ptr[result], eax
        mov dword ptr[result + 4], edx

        pop ebx
    }

    return result;
}
#endif //_M_IX86