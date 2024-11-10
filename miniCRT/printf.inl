#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <tchar.h>

#ifdef PRINTF_FN
#undef PRINTF_FN
#undef PRINTF_DESTLENGTH
#undef PRINTF_PUSHCHAR
#endif

#define PRINTF_ANSI_TO_UNICODE(x)     (TCHAR)(x)
#define PRINTF_UNICODE_TO_ANSI(x)     (TCHAR)((x>=0x20&&x<0x80)?x:'?')

#ifdef PRINTF_SIZEONLY

#ifdef UNICODE
#define PRINTF_FN mini_vswprintf_size
#else
#define PRINTF_FN mini_vsprintf_size
#endif

#define PRINTF_DESTLENGTH() (1)
#define PRINTF_PUSHCHAR(x)  dest_offset++,x;

#else // PRINTF_SIZEONLY

#ifdef UNICODE
#define PRINTF_FN mini_vswprintf_s
#else
#define PRINTF_FN mini_vsprintf_s
#endif

#define PRINTF_DESTLENGTH()  (dest_offset < len - 1)
#define PRINTF_PUSHCHAR(x)   szDest[dest_offset++] = x;

#endif // PRINTF_SIZEONLY

extern "C" int __cdecl PRINTF_FN (
#ifndef PRINTF_SIZEONLY
    LPTSTR szDest,
    unsigned int len,
#endif
    LPCTSTR szFmt,
    va_list marker)
{
    unsigned int dest_offset = 0;
    unsigned int src_offset = 0;
    unsigned int i;

    BOOL leadingzero;
    BOOL leftalign;
    BOOL short_prefix;
    BOOL long_prefix;
    unsigned int element_len;
    int precision = -1; // -1 means no precision specified

    while (szFmt[src_offset] != '\0' && PRINTF_DESTLENGTH()) {
        if (szFmt[src_offset] == '%') {
            src_offset++;
            leadingzero = FALSE;
            leftalign = FALSE;
            long_prefix = FALSE;
            short_prefix = FALSE;
            element_len = 0;

            if (szFmt[src_offset] == '-') {
                leftalign = TRUE;
                src_offset++;
            }
            if (szFmt[src_offset] == '0') {
                leadingzero = TRUE;
                src_offset++;
            }
            while (szFmt[src_offset] >= '0' && szFmt[src_offset] <= '9') {
                element_len = element_len * 10 + szFmt[src_offset] - '0';
                src_offset++;
            }
            // Precision handling
            if (szFmt[src_offset] == '.') {
                src_offset++;
                precision = 0;
                while (szFmt[src_offset] >= '0' && szFmt[src_offset] <= '9') {
                    precision = precision * 10 + szFmt[src_offset] - '0';
                    src_offset++;
                }
            }
            if (szFmt[src_offset] == 'h') {
                short_prefix = TRUE;
                src_offset++;
            }
            else if (szFmt[src_offset] == 'l') {
                long_prefix = TRUE;
                src_offset++;
            }

            if (element_len == 0) {
                element_len = (unsigned int)-1;
            }

            switch (szFmt[src_offset]) {
            case '%':
                PRINTF_PUSHCHAR('%');
                break;

            case 'c':
            {
                //
                //  The compiler always upconverts chars to ints when
                //  creating variable arguments.  We have to mirror
                //  that semantic here.  MSVC gets this "right" by
                //  allowing these to be symmetrical and upconverting
                //  both, but gcc gets it "wrong" and explodes by
                //  upconverting one and not the other (then printing
                //  a warning blaming this code.)
                //

                i = (TCHAR)va_arg(marker, int);
                PRINTF_PUSHCHAR((TCHAR)i);
            }
            break;
            case 's':
            {
                LPTSTR str = va_arg(marker, LPTSTR);
                LPSTR  short_str = (LPSTR)str;
                LPWSTR long_str = (LPWSTR)str;

                if (str == NULL) {
                    short_str = "(null)";
                    short_prefix = TRUE;
                    long_prefix = FALSE;
                }

                if (!short_prefix && !long_prefix) {
#ifdef UNICODE
                    long_prefix = TRUE;
#else
                    short_prefix = TRUE;
#endif
                }

                if (element_len != (unsigned int)-1 && !leftalign) {
                    unsigned int str_len = 0;
                    if (short_prefix) {
                        while (short_str[str_len] != '\0') str_len++;
                    }
                    else if (long_prefix) {
                        while (long_str[str_len] != '\0') str_len++;
                    }

                    while (element_len > str_len && PRINTF_DESTLENGTH()) {
                        PRINTF_PUSHCHAR(' ');
                        element_len--;
                    }
                }
                if (short_prefix) {
                    while (*short_str != '\0' && PRINTF_DESTLENGTH() && element_len) {
#ifdef UNICODE
                        PRINTF_PUSHCHAR(PRINTF_ANSI_TO_UNICODE(*short_str));
#else
                        PRINTF_PUSHCHAR(*short_str);
#endif
                        short_str++;
                        element_len--;
                    }
                }
                else if (long_prefix) {
                    while (*long_str != '\0' && PRINTF_DESTLENGTH() && element_len) {
#ifdef UNICODE
                        PRINTF_PUSHCHAR(*long_str);
#else
                        PRINTF_PUSHCHAR(PRINTF_UNICODE_TO_ANSI(*long_str));
#endif
                        long_str++;
                        element_len--;
                    }
                }

                if (leftalign) {
                    while (element_len-- && PRINTF_DESTLENGTH()) {
                        PRINTF_PUSHCHAR(' ');
                    }
                }
            }
            break;
            case 'u':
            case 'd':
            case 'i':
            case 'x':
            case 'X':
            {
                unsigned int num, tempnum;
                unsigned int divisor, digits;
                unsigned int radix = (szFmt[src_offset] == 'x' || szFmt[src_offset] == 'X') ? 16 : 10;
                BOOL uppercase = (szFmt[src_offset] == 'X');

                //
                //  If we're %i we're base 10, if we're %x we're
                //  base 16
                //

                if (szFmt[src_offset] == 'x') {
                    radix = 16;
                }

                num = va_arg(marker, int);

                //
                //  Count the number of digits we have in the user's
                //  input.  Stop if we hit the format specifier.
                //  Code below will preserve low order values.
                //

                divisor = 1;
                digits = 1;
                tempnum = num;
                while (tempnum > radix - 1 && digits < element_len) {
                    divisor *= radix;
                    tempnum = num / divisor;
                    digits++;
                }

                //
                //  If the field specifier is larger, pad it with
                //  either a zero or space depending on the format
                //

                if (element_len != (unsigned int)-1 && digits < element_len) {
                    tempnum = element_len - digits;
                    while (tempnum > 0) {
                        if (leadingzero) {
                            PRINTF_PUSHCHAR('0');
                        }
                        else {
                            PRINTF_PUSHCHAR(' ');
                        }
                        if (!PRINTF_DESTLENGTH()) {
                            break;
                        }
                        tempnum--;
                    }
                }

                do {
                    tempnum = (num / divisor) % radix;

                    if (tempnum > 9) {
                        PRINTF_PUSHCHAR((UCHAR)tempnum + (uppercase? 'A':'a') - 10);
                    }
                    else {
                        PRINTF_PUSHCHAR((UCHAR)tempnum + '0');
                    }

                    if (!PRINTF_DESTLENGTH()) {
                        break;
                    }

                    divisor /= radix;
                    digits--;

                } while (digits > 0);

            }
            break;
            case 'p':
            {
                // Handle pointer formatting as hexadecimal with "0x" prefix
                unsigned long long ptr = (unsigned long long)va_arg(marker, void*);
                PRINTF_PUSHCHAR('0');
                PRINTF_PUSHCHAR('x');
                // Insert hexadecimal digits for the pointer value
            }
            break;

            case 'f':
            case 'e':
            case 'g':
            {
                double num = va_arg(marker, double);
                TCHAR float_str[32];
                auto FloatToStr = [](double num, TCHAR* dest, int maxLen, int precision) -> void {
                    if (maxLen <= 0) return;

                    // Handle negative numbers
                    int dest_offset = 0;
                    if (num < 0) {
                        if (dest_offset < maxLen - 1) dest[dest_offset++] = _T('-');
                        num = -num;
                    }

                    // Extract the integer part
                    unsigned long long integerPart = (unsigned long long)num;
                    double fractionalPart = num - integerPart;

                    // Convert integer part to string
                    TCHAR intStr[20];  // Buffer for integer part, assuming it's large enough
                    int intLen = 0;
                    do {
                        intStr[intLen++] = _T('0') + (integerPart % 10);
                        integerPart /= 10;
                    } while (integerPart > 0 && intLen < sizeof(intStr) / sizeof(intStr[0]));

                    // Reverse integer part into destination buffer
                    for (int i = intLen - 1; i >= 0 && dest_offset < maxLen - 1; i--) {
                        dest[dest_offset++] = intStr[i];
                    }

                    // Add the decimal point
                    if (precision > 0 && dest_offset < maxLen - 1) {
                        dest[dest_offset++] = _T('.');
                    }

                    // Convert fractional part to string with the specified precision
                    for (int i = 0; i < precision && dest_offset < maxLen - 1; i++) {
                        fractionalPart *= 10;
                        int digit = (int)fractionalPart;
                        dest[dest_offset++] = _T('0') + digit;
                        fractionalPart -= digit;
                    }

                    // Null-terminate the string
                    if (dest_offset < maxLen) {
                        dest[dest_offset] = _T('\0');
                    }
                };
                FloatToStr(num, float_str, 32, (precision >= 0 ? precision : 6));

                // Output formatted float string
                for (i = 0; float_str[i] != '\0' && PRINTF_DESTLENGTH(); i++) {
                    PRINTF_PUSHCHAR(float_str[i]);
                }
            }
            break;
            default:
            {
                LPTSTR szErr = _T("FMTERR");
                i = 0;
                while (PRINTF_DESTLENGTH() && szErr[i] != '\0') {
                    PRINTF_PUSHCHAR(szErr[i++]);
                }
            }
            break;
            }

            src_offset++;

        }
        else {
            PRINTF_PUSHCHAR(szFmt[src_offset++]);
        }
    }

#ifndef PRINTF_SIZEONLY
    if (dest_offset >= len || szFmt[src_offset] != '\0') {
        szDest[0] = '\0';
        return -1;
    }
#endif
    PRINTF_PUSHCHAR('\0');

#ifndef PRINTF_SIZEONLY
    dest_offset--;
#endif

    return dest_offset;
}