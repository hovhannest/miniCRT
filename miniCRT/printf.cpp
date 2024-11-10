#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

extern "C" int _fltused = 0;

extern "C" int __cdecl mini_vswprintf_size(LPCWSTR, va_list);
extern "C" int __cdecl mini_vsprintf_size(LPCSTR, va_list);
extern "C" int __cdecl mini_vswprintf_s(LPCWSTR, unsigned int, LPCWSTR, va_list);
extern "C" int __cdecl mini_vsprintf_s(LPCSTR, unsigned int, LPCSTR, va_list);

extern "C" int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    int len = mini_vsprintf_s(buffer, sizeof(buffer), format, args);

    if (len > 0) {
        DWORD written;
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, len, &written, nullptr);  // stdout
    }

    va_end(args);
    return len;
}

extern "C" int wprintf(const wchar_t* format, ...) {
    va_list args;
    va_start(args, format);

    wchar_t buffer[1024];
    int len = mini_vswprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), format, args);

    if (len > 0) {
        DWORD written;
        WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, len * sizeof(wchar_t), &written, nullptr);  // stdout
    }

    va_end(args);
    return len;
}

extern "C" int fprintf(HANDLE stream, const char* format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    int len = mini_vsprintf_s(buffer, sizeof(buffer), format, args);

    if (len > 0) {
        DWORD written;
        WriteFile(stream, buffer, len, &written, nullptr);
    }

    va_end(args);
    return len;
}

extern "C" int fwprintf(HANDLE stream, const wchar_t* format, ...) {
    va_list args;
    va_start(args, format);

    wchar_t buffer[1024];
    int len = mini_vswprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), format, args);

    if (len > 0) {
        DWORD written;
        WriteFile(stream, buffer, len * sizeof(wchar_t), &written, nullptr);
    }

    va_end(args);
    return len;
}

extern "C" int sprintf(char* buffer, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int len = mini_vsprintf_s(buffer, 1024, format, args);
    va_end(args);
    return len;
}

extern "C" int snprintf(char* buffer, size_t count, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int len = mini_vsprintf_s(buffer, (unsigned int)count, format, args);
    va_end(args);
    return len;
}

extern "C" int vsprintf(char* buffer, const char* format, va_list args) {
    return mini_vsprintf_s(buffer, 1024, format, args);
}

extern "C" int vsnprintf(char* buffer, size_t count, const char* format, va_list args) {
    return mini_vsprintf_s(buffer, (unsigned int)count, format, args);
}

extern "C" void _wassert(const wchar_t* expression, const wchar_t* file, unsigned line) {
    wchar_t buffer[512];
    wchar_t messageFormat[] = L"Assertion failed: %s\nFile: %s\nLine: %u\n";

    // Format the assertion message using mini_vsprintf_s helper
    int length = wprintf(buffer, sizeof(buffer) / sizeof(wchar_t), messageFormat, expression, file, line);

    ExitProcess(1);
}

extern "C" int __cdecl
sprintf_s(char* szDest, unsigned int len, char* szFmt, ...)
{
    va_list marker;
    int out_len;

    va_start(marker, szFmt);
    out_len = mini_vsprintf_s(szDest, len, szFmt, marker);
    va_end(marker);
    return out_len;
}
extern "C" int __cdecl
swprintf_s(wchar_t* szDest, unsigned int len, wchar_t* szFmt, ...)
{
    va_list marker;
    int out_len;

    va_start(marker, szFmt);
    out_len = mini_vswprintf_s(szDest, len, szFmt, marker);
    va_end(marker);
    return out_len;
}
extern "C" int __cdecl
swprintf(wchar_t* szDest, const wchar_t* szFmt, ...)
{
    va_list marker;
    int out_len;

    va_start(marker, szFmt);
    out_len = mini_vswprintf_s(szDest, -1, szFmt, marker);
    va_end(marker);
    return out_len;
}

extern "C" int __cdecl 
vswprintf(LPCWSTR szDest, unsigned int len, LPCWSTR szFmt, va_list marker)
{
    return mini_vswprintf_s(szDest, len, szFmt, marker);
}