#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

// Define this in all prijects
#ifndef _NO_CRT_STDIO_INLINE
#define _NO_CRT_STDIO_INLINE
#endif //_NO_CRT_STDIO_INLINE
// Call this function at exit manually.
extern "C" void __cdecl mini_exit(void);


