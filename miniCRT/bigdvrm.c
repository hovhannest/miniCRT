#ifdef _M_IX86
#include <stdint.h>

typedef struct {
    uint64_t quotient;
    uint64_t remainder;
} div_result;

extern uint64_t _aulldiv(uint64_t dividend, uint32_t divisor);
extern uint64_t _aullrem(uint64_t dividend, uint32_t divisor);
extern int64_t _alldiv(int64_t dividend, int64_t divisor);
extern int64_t _allrem(int64_t dividend, int64_t divisor);

div_result _aulldvrm(uint64_t dividend, uint32_t divisor) {
    div_result result;

    __asm {
        ; Push the arguments for the next function
        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        ; Get the remainder
        call _aullrem

        ; Save the remainder into registers that will be preserved
        mov ebx, edx
        mov esi, eax

        ; Push the arguments for the next function
        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        ; Get the result
        call _aulldiv

        ; Store the result and remainder
        mov dword ptr[result.quotient], eax
        mov dword ptr[result.quotient + 4], edx
        mov dword ptr[result.remainder], esi
        mov dword ptr[result.remainder + 4], ebx
    }

    return result;
}

div_result _alldvrm(int64_t dividend, int64_t divisor) {
    div_result result;

    __asm {
        ; Push the arguments for the next function
        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        ; Get the remainder
        call _allrem

        ; Save the remainder into registers that will be preserved
        mov ebx, edx
        mov esi, eax

        ; Push the arguments for the next function
        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        mov edx, dword ptr[dividend + 4]
        mov eax, dword ptr[dividend]
        push edx
        push eax

        ; Get the result
        call _alldiv

        ; Store the result and remainder
        mov dword ptr[result.quotient], eax
        mov dword ptr[result.quotient + 4], edx
        mov dword ptr[result.remainder], esi
        mov dword ptr[result.remainder + 4], ebx
    }

    return result;
}
#endif //_M_IX86