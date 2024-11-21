// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the $safeprojectname$_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// $safeprojectname$_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef $safeprojectname$_EXPORTS
#define $projectname$_API __declspec(dllexport)
#else
#define $safeprojectname$_API __declspec(dllimport)
#endif

//bool $safeprojectname$_API $safeprojectname$(void* params) noexcept;
