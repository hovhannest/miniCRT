#ifdef _M_IX86
#include <stdint.h>

uint64_t _aullrem(uint64_t dividend, uint32_t divisor) {
    uint64_t remainder;

    __asm {
        ; Check if the divisor is 64 - bit, if so, trigger overflow
        mov eax, dword ptr[divisor + 4]
        test eax, eax
        jnz aullrem_overflow

        ; Divide the high 32 bits by the low 32 bits and leave the remainder in edx
        mov ecx, dword ptr[divisor]
        xor edx, edx
        mov eax, dword ptr[dividend + 4]
        div ecx
        mov eax, dword ptr[dividend]
        div ecx
        mov eax, edx
        xor edx, edx
        jmp aullrem_done

        aullrem_overflow :
        //int 3
        xor edx, edx
        xor eax, eax

        aullrem_done :
        mov dword ptr[remainder], eax
            mov dword ptr[remainder + 4], edx
    }

    return remainder;
}

int64_t _allrem(int64_t dividend, int64_t divisor) {
    int64_t remainder;

    __asm {
        push ebx
        xor ebx, ebx

        ; Check if the divisor is negative, if so, convert to positive and increment ebx
        mov edx, dword ptr[divisor + 4]
        mov eax, dword ptr[divisor]
        bt edx, 31
        jnc allrem_positive_divisor

        inc ebx
        neg edx
        neg eax
        sbb edx, 0

        allrem_positive_divisor:
        push edx
            push eax

            ; Check if the dividend is negative, if so, convert to positive and increment ebx
            mov edx, dword ptr[dividend + 4]
            mov eax, dword ptr[dividend]
            bt edx, 31
            jnc allrem_positive_dividend

            inc ebx
            neg edx
            neg eax
            sbb edx, 0

            allrem_positive_dividend:
        push edx
            push eax

            ; Call the unsigned remainder function
            call _aullrem

            ; Check if an odd number of negative numbers were found, if so, convert result to negative
            bt ebx, 0
            jnc allrem_return_positive

            neg edx
            neg eax
            sbb edx, 0

            allrem_return_positive:
        pop ebx
            mov dword ptr[remainder], eax
            mov dword ptr[remainder + 4], edx
    }

    return remainder;
}
#endif //_M_IX86