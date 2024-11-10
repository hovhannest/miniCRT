
#include "minicrt.h"

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

    test_memcpy();
    test_memmove();
    test_memset();
    test_memcmp();
    test_fgets();

    static int i = 0;
    static A a;

    mini_exit();
	ExitProcess(0);
	return SUCSESS_RET_CODE; 
}
#pragma warning(pop)
