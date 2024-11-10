#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <tchar.h>

extern "C" int __cdecl
atoi(char* str)
{
    int ret = 0;
    while (*str >= '0' && *str <= '9') {
        ret *= 10;
        ret += *str - '0';
        str++;
    }
    return ret;
}
extern "C" int __cdecl
_wtoi(const wchar_t* str)
{
    int ret = 0;
    while (*str >= '0' && *str <= '9') {
        ret *= 10;
        ret += *str - '0';
        str++;
    }
    return ret;
}

extern "C" int __cdecl
strcat_s(char* dest, size_t len, const char* src)
{
    unsigned int i, j;
    for (i = 0; dest[i] != '\0' && i < len; i++);
    for (j = 0; src[j] != '\0' && i < len - 1; ) {
        dest[i++] = src[j++];
    }
    dest[i++] = '\0';
    return 0;
}
extern "C" int __cdecl
wcscat_s(wchar_t* dest, size_t len, const wchar_t* src)
{
    unsigned int i, j;
    for (i = 0; dest[i] != '\0' && i < len; i++);
    for (j = 0; src[j] != '\0' && i < len - 1; ) {
        dest[i++] = src[j++];
    }
    dest[i++] = '\0';
    return 0;
}

extern "C" char* __cdecl
strncat(char* dest, const char* src, size_t len)
{
    unsigned int i, j;
    for (i = 0; dest[i] != '\0'; i++);
    for (j = 0; src[j] != '\0' && j < len; ) {
        dest[i++] = src[j++];
    }
    dest[i++] = '\0';
    return dest;
}
extern "C" wchar_t* __cdecl
wcsncat(wchar_t* dest, const wchar_t* src, size_t len)
{
    unsigned int i, j;
    for (i = 0; dest[i] != '\0'; i++);
    for (j = 0; src[j] != '\0' && j < len; ) {
        dest[i++] = src[j++];
    }
    dest[i++] = '\0';
    return dest;
}

extern "C" const char* __cdecl
strchr(const char* str, const int ch)
{
    const char* ptr = str;
    while (*ptr != '\0' && *ptr != ch) ptr++;
    if (*ptr == ch) return (char*)ptr;
    return NULL;
}
extern "C" const wchar_t* __cdecl
wcschr(const wchar_t* str, wchar_t ch)
{
    const wchar_t* ptr = str;
    while (*ptr != '\0' && *ptr != ch) ptr++;
    if (*ptr == ch) return (wchar_t*)ptr;
    return NULL;
}

extern "C" const char* __cdecl
strrchr(const char* str, const int ch)
{
    const char* ptr = str;
    while (*ptr != '\0') ptr++;
    while (*ptr != ch && ptr > str) ptr--;
    if (*ptr == ch) return (char*)ptr;
    return NULL;
}
extern "C" const wchar_t* __cdecl
wcsrchr(const wchar_t* str, wchar_t ch)
{
    const wchar_t* ptr = str;
    while (*ptr != '\0') ptr++;
    while (*ptr != ch && ptr > str) ptr--;
    if (*ptr == ch) return (wchar_t*)ptr;
    return NULL;
}

extern "C" size_t __cdecl
strlen(const char* str)
{
    // return lstrlenA(str);
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}
extern "C" size_t __cdecl
wcslen(const wchar_t* str)
{
    // return lstrlenW(str);
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

extern "C" const char* __cdecl
strstr(const char* str, const char* search)
{
    const char* ptr = str;
    int i;
    while (*ptr != '\0') {
        for (i = 0; ptr[i] == search[i] && search[i] != '\0' && ptr[i] != '\0'; i++);
        if (search[i] == '\0') return (char*)ptr;
        ptr++;
    }
    return NULL;
}
extern "C" const wchar_t* __cdecl
wcsstr(const wchar_t* str, const wchar_t* search)
{
    const wchar_t* ptr = str;
    int i;
    while (*ptr != '\0') {
        for (i = 0; ptr[i] == search[i] && search[i] != '\0' && ptr[i] != '\0'; i++);
        if (search[i] == '\0') return (wchar_t*)ptr;
        ptr++;
    }
    return NULL;
}

extern "C" int __cdecl
toupper(int c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}
extern "C" wint_t  __cdecl
towupper(wint_t  c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

extern "C" int __cdecl
tolower(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}
extern "C" wint_t __cdecl
towlower(wint_t c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

extern "C" char* __cdecl
strupr(char* str)
{
    char* ptr = str;

    while (*ptr != '\0') {
        *ptr = (char)toupper(*ptr);
        ptr++;
    }
    return str;
}
extern "C" wchar_t* __cdecl
wcsupr(wchar_t* str)
{
    wchar_t* ptr = str;

    while (*ptr != '\0') {
        *ptr = (wchar_t)towupper(*ptr);
        ptr++;
    }
    return str;
}

extern "C" char* __cdecl
strlwr(char* str)
{
    char* ptr = str;

    while (*ptr != '\0') {
        *ptr = (char)tolower(*ptr);
        ptr++;
    }
    return str;
}
extern "C" wchar_t* __cdecl
wcslwr(wchar_t* str)
{
    wchar_t* ptr = str;

    while (*ptr != '\0') {
        *ptr = (wchar_t)towlower(*ptr);
        ptr++;
    }
    return str;
}

extern "C" int __cdecl
strncmp(const char* str1, const char* str2, size_t count)
{
    const char* ptr1 = str1;
    const char* ptr2 = str2;
    size_t remaining = count;

    while (TRUE) {
        if (*ptr1 < *ptr2) {
            return -1;
        }
        else if (*ptr1 > *ptr2) {
            return 1;
        }
        else if (*ptr1 == '\0') {
            return 0;
        }

        ptr1++;
        ptr2++;
        remaining--;

        if (remaining == 0) {
            return 0;
        }
    }
    return 0;
}
extern "C" int __cdecl
wcsncmp(const wchar_t* str1, const wchar_t* str2, size_t count)
{
    const wchar_t* ptr1 = str1;
    const wchar_t* ptr2 = str2;
    size_t remaining = count;

    while (TRUE) {
        if (*ptr1 < *ptr2) {
            return -1;
        }
        else if (*ptr1 > *ptr2) {
            return 1;
        }
        else if (*ptr1 == '\0') {
            return 0;
        }

        ptr1++;
        ptr2++;
        remaining--;

        if (remaining == 0) {
            return 0;
        }
    }
    return 0;
}

extern "C" int __cdecl
strcmp(const char* str1, const char* str2)
{
    return strncmp(str1, str2, (unsigned int)-1);
}
extern "C" int __cdecl
wcscmp(const wchar_t* str1, const wchar_t* str2)
{
    return wcsncmp(str1, str2, (unsigned int)-1);
}

extern "C" int __cdecl
_strnicmp(const char* str1, const char* str2, size_t count)
{
    const char* ptr1 = str1;
    const char* ptr2 = str2;
    size_t remaining = count;

    while (TRUE) {
        if (toupper(*ptr1) < toupper(*ptr2)) {
            return -1;
        }
        else if (toupper(*ptr1) > toupper(*ptr2)) {
            return 1;
        }
        else if (*ptr1 == '\0') {
            return 0;
        }
        ptr1++;
        ptr2++;
        remaining--;

        if (remaining == 0) {
            return 0;
        }
    }
    return 0;
}
extern "C" int __cdecl
_wcsnicmp(const wchar_t* str1, const wchar_t* str2, size_t count)
{
    const wchar_t* ptr1 = str1;
    const wchar_t* ptr2 = str2;
    size_t remaining = count;

    while (TRUE) {
        if (towupper(*ptr1) < towupper(*ptr2)) {
            return -1;
        }
        else if (towupper(*ptr1) > towupper(*ptr2)) {
            return 1;
        }
        else if (*ptr1 == '\0') {
            return 0;
        }
        ptr1++;
        ptr2++;
        remaining--;

        if (remaining == 0) {
            return 0;
        }
    }
    return 0;
}
extern "C" int __cdecl
strnicmp(const char* str1, const char* str2, size_t count)
{
    return _strnicmp(str1, str2, count);
}
extern "C" int __cdecl
wcsnicmp(const wchar_t* str1, const wchar_t* str2, size_t count)
{
    return _wcsnicmp(str1, str2, count);
}

extern "C" int __cdecl
stricmp(const char* str1, const char* str2)
{
    return _strnicmp(str1, str2, -1);
}
extern "C" int __cdecl
wcsicmp(const wchar_t* str1, const wchar_t* str2)
{
    return _wcsnicmp(str1, str2, -1);
}

extern "C" char* __cdecl
strtok_s(char* str, const char* match, char** context)
{
    char* next;
    if (str != NULL) {
        *context = str;
    }

    next = *context;
    if (next == NULL) {
        return NULL;
    }

    while (*next != match[0] && *next != '\0') next++;

    if (*next == match[0]) {
        char* ret = *context;
        *next = '\0';
        *context = ++next;
        return ret;
    }
    else {
        char* ret = *context;
        *context = NULL;
        return ret;
    }
}
extern "C" wchar_t* __cdecl
wcstok_s(wchar_t* str, const wchar_t* match, wchar_t** context)
{
    wchar_t* next;
    if (str != NULL) {
        *context = str;
    }

    next = *context;
    if (next == NULL) {
        return NULL;
    }

    while (*next != match[0] && *next != '\0') next++;

    if (*next == match[0]) {
        wchar_t* ret = *context;
        *next = '\0';
        *context = ++next;
        return ret;
    }
    else {
        wchar_t* ret = *context;
        *context = NULL;
        return ret;
    }
}

/*char* STRTOK_CTX;
extern "C" char* __cdecl
strtok(char* str, const char* match)
{
    return strtok_s(str, match, &STRTOK_CTX);
}
wchar_t* context;
extern "C" wchar_t* __cdecl
wcstok(wchar_t* str, const wchar_t* match)
{
    return wcstok_s(str, match, &context);
}*/

extern "C" size_t __cdecl
strspn(const char* str, const char* chars)
{
    DWORD len = 0;
    DWORD i;

    for (len = 0; str[len] != '\0'; len++) {
        for (i = 0; chars[i] != '\0'; i++) {
            if (str[len] == chars[i]) {
                break;
            }
        }
        if (chars[i] == '\0') {
            return len;
        }
    }

    return len;
}
extern "C" size_t __cdecl
wcsspn(const wchar_t* str, const wchar_t* chars)
{
    DWORD len = 0;
    DWORD i;

    for (len = 0; str[len] != '\0'; len++) {
        for (i = 0; chars[i] != '\0'; i++) {
            if (str[len] == chars[i]) {
                break;
            }
        }
        if (chars[i] == '\0') {
            return len;
        }
    }

    return len;
}

extern "C" size_t __cdecl
strcspn(const char* str, const char* match)
{
    DWORD len = 0;
    DWORD i;

    for (len = 0; str[len] != '\0'; len++) {
        for (i = 0; match[i] != '\0'; i++) {
            if (str[len] == match[i]) {
                return len;
            }
        }
    }

    return len;
}
extern "C" size_t __cdecl
wcscspn(const wchar_t* str, const wchar_t* match)
{
    DWORD len = 0;
    DWORD i;

    for (len = 0; str[len] != '\0'; len++) {
        for (i = 0; match[i] != '\0'; i++) {
            if (str[len] == match[i]) {
                return len;
            }
        }
    }

    return len;
}
