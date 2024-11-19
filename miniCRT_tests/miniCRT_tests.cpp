
// from https://github.com/SpoilerScriptsGroup/RetrievAL/blob/3b56fd0238dc9046e04a4dd982242b0f0ba39264/SpoilerAL-winmm.dll/crt/math/ftol3.c#L264

#include "minicrt.h"

#include <EASTL/string.h>
#include <EASTL/vector.h>

void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
    return new uint8_t[size];
}
void* __cdecl operator new[](size_t size, size_t, size_t, char const*, int, unsigned int, char const*, int)
{
    return new uint8_t[size];
}


#pragma  warning(push)
#pragma warning(disable : 4996)
#include "test_alloc.h"
#include "test_printf.h"
#include "test_string.h"
#include "test_file_io.h"
#include "test_mem.h"

#include <windows.h>

struct A
{
    A() 
    {
    }
    ~A() {}
};

#if defined _CONSOLE
#define SUCSESS_RET_CODE 0
int mainCRTStartup() {
#elif defined _WINDOWS
#define SUCSESS_RET_CODE
void WinMainCRTStartup() {
#endif // _CONSOLE or _WINDOWS
    test_malloc();
    test_realloc();
    test_calloc();

    test_atoi();
    test_wtoi();
    test_strcat_s();
    test_wcscat_s();
    test_strncat();
    test_wcsncat();
    test_strchr();
    test_wcschr();
    test_strlen();
    test_wcslen();
    test_strstr();
    test_wcsstr();
    test_toupper();
    test_towupper();
    test_strtok_s();
    test_wcstok_s();

    test_wprintf();
    test_fwprintf();
    test_swprintf();

    test_fopen_read();
    test_fopen_write();
    test_fopen_append();
    test_fopen_invalid_mode();
    test_fclose_invalid_file();
    test_fclose_valid_file();
    test_fgets();

    test_memcpy();
    test_memmove();
    test_memset();
    test_memcmp();

    static int i = 0;
    static A a;

    eastl::string str1 = "Hello, EASTL!";
    str1 += " EEee!\n";

    eastl::vector<eastl::string> vec;
    vec.push_back("asd1\n");
    vec.push_back("asd2\n");

    printf(str1.c_str());

    for each (auto var in vec)
    {
        printf(var.c_str());
    }

    mini_exit();
	ExitProcess(0);
	return SUCSESS_RET_CODE; 
}
#pragma warning(pop)
