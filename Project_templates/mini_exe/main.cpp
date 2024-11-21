#include "minicrt.h"

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

#if defined _CONSOLE
#define SUCSESS_RET_CODE 0
int mainCRTStartup() {
#elif defined _WINDOWS
#define SUCSESS_RET_CODE
void WinMainCRTStartup() {
#endif // _CONSOLE or _WINDOWS

    mini_exit();
	ExitProcess(0);
	return SUCSESS_RET_CODE; 
}
#pragma warning(pop)
