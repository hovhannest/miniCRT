#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#include <stdio.h>
#include <stdarg.h>

extern "C" FILE * __cdecl __acrt_iob_func(unsigned index) {
    // Return the standard file pointer for stdin, stdout, or stderr.
    // These are usually defined in the C runtime.
    if (index == 0) {
        return stdin;
    }
    else if (index == 1) {
        return stdout;
    }
    else if (index == 2) {
        return stderr;
    }
    return NULL;  // Return NULL if invalid index.
}

extern "C" int __cdecl __stdio_common_vfprintf(
    unsigned __int64 _Options,  // options for customizing behavior
    FILE* _Stream,              // the output stream (stdout, stderr, etc.)
    const char* _Format,        // the format string
    _locale_t _Locale,         // locale information (optional)
    va_list _ArgList             // the arguments to format
) {
    // Use vfprintf to write the formatted string
    return printf(_Format, _ArgList);
}