#ifdef _M_IX86
#include <stdint.h>

uint64_t _allshl(uint64_t value, uint8_t shift) {
    uint64_t result;

    __asm {
        mov cl, shift
        mov eax, dword ptr[value]
        mov edx, dword ptr[value + 4]

        ; If the shift is for more than 64 bits, return zero
        cmp cl, 64
        jae allshl_no_shift

        ; If the shift is for more than 32 bits, handle long shift
        cmp cl, 32
        jae allshl_long_shift

        ; Handle short shift
        shld edx, eax, cl
        shl eax, cl
        jmp allshl_done

        allshl_long_shift :
        sub cl, 32
            shl eax, cl
            mov edx, eax
            xor eax, eax
            jmp allshl_done

            allshl_no_shift :
        xor eax, eax
            xor edx, edx

            allshl_done :
        mov dword ptr[result], eax
            mov dword ptr[result + 4], edx
    }

    return result;
}

uint64_t _aullshr(uint64_t value, uint8_t shift) {
    uint64_t result;

    __asm {
        mov cl, shift
        mov eax, dword ptr[value]
        mov edx, dword ptr[value + 4]

        ; If the shift is for more than 64 bits, return zero
        cmp cl, 64
        jae aullshr_no_shift

        ; If the shift is for more than 32 bits, handle long shift
        cmp cl, 32
        jae aullshr_long_shift

        ; Handle short shift
        shrd eax, edx, cl
        shr edx, cl
        jmp aullshr_done

        aullshr_long_shift :
        sub cl, 32
            shr edx, cl
            mov eax, edx
            xor edx, edx
            jmp aullshr_done

            aullshr_no_shift :
        xor eax, eax
            xor edx, edx

            aullshr_done :
        mov dword ptr[result], eax
            mov dword ptr[result + 4], edx
    }

    return result;
}

uint64_t _allshr(uint64_t value, uint8_t shift) {
    return _aullshr(value, shift);
}
#endif // _M_IX86