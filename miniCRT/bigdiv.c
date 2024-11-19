#ifdef _M_IX86
#include <stdint.h>

uint64_t _aulldiv(uint64_t dividend, uint32_t divisor) {
    uint32_t high, low;
    uint64_t result;

    __asm {
        ; Check if the high part of the divisor is non - zero
        mov eax, divisor
        test eax, eax
        jnz aulldiv_overflow

        push ebx

        ; Divide the high 32 bits by the low 32 bits, save it in ebx,
        ; and leave the remainder in edx.Then, divide the low 32 bits
        ; plus the remainder, which must fit in a 32 - bit value.To satisfy
        ; the calling convention, move ebx to edx, and return.

        mov ecx, divisor
        xor edx, edx
        mov eax, dword ptr[dividend + 4]
        div ecx
        mov ebx, eax
        mov eax, dword ptr[dividend]
        div ecx
        mov edx, ebx
        pop ebx
        jmp aulldiv_done

        aulldiv_overflow :
        //int 3
        xor edx, edx
        xor eax, eax

        aulldiv_done :
        mov dword ptr[result], eax
            mov dword ptr[result + 4], edx
    }

    return result;
}

int64_t _alldiv(int64_t dividend, int64_t divisor) {
    int64_t result;
    uint32_t ebx = 0;

    __asm {
        push ebx
        xor ebx, ebx

        ; Check if the divisor is positive or negative.If negative, increment
        ; ebx to indicate another negative number was found, and convert it to
        ; positive

        alldiv_test_divisor :
        mov edx, dword ptr[divisor + 4]
            mov eax, dword ptr[divisor]
            bt edx, 31
            jnc alldiv_positive_divisor

            inc ebx
            neg edx
            neg eax
            sbb edx, 0

            ; Push the now positive divisor onto the stack, thus moving esp

            alldiv_positive_divisor :
        push edx
            push eax

            ; Check if the dividend is positive or negative.If negative, increment
            ; ebx to indicate another negative number was found, and convert it to
            ; positive

            mov edx, dword ptr[dividend + 4]
            mov eax, dword ptr[dividend]
            bt edx, 31
            jnc alldiv_positive_dividend

            inc ebx
            neg edx
            neg eax
            sbb edx, 0

            ; Push the now positive dividend onto the stack, thus moving esp

            alldiv_positive_dividend :
        push edx
            push eax

            ; Call the positive version of this routine

            call _aulldiv

            ; Test if an odd number of negative numbers were found.If so, convert the
            ; result back to negative, otherwise return the result as is.

            bt ebx, 0
            jnc alldiv_return_positive

            neg edx
            neg eax
            sbb edx, 0

            alldiv_return_positive:
        pop ebx
            mov dword ptr[result], eax
            mov dword ptr[result + 4], edx
    }

    return result;
}
#endif //_M_IX86
