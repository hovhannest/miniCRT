#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>
#include <cstdio>

extern "C" FILE* __cdecl fopen(const char* filename, const char* mode) {
    DWORD access = 0;
    DWORD creation = 0;
    DWORD shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

    if (strchr(mode, 'r')) {
        access |= GENERIC_READ;
        creation = OPEN_EXISTING;
    }
    if (strchr(mode, 'w')) {
        access |= GENERIC_WRITE;
        creation = CREATE_ALWAYS;
    }
    if (strchr(mode, 'a')) {
        access |= FILE_APPEND_DATA;
        creation = OPEN_ALWAYS;
    }
    if (strchr(mode, '+') || strchr(&mode[1], '+')) {
        access |= GENERIC_READ | GENERIC_WRITE;
    }

    HANDLE file = CreateFileA(filename, access, shareMode, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
    return (FILE*)(file != INVALID_HANDLE_VALUE ? file : NULL);
}

extern "C" FILE * __cdecl _wfopen(const wchar_t* filename, const wchar_t* mode) {
    DWORD access = 0;
    DWORD creation = 0;
    DWORD shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;

    if (wcschr(mode, L'r')) {
        access |= GENERIC_READ;
        creation = OPEN_EXISTING;
    }
    if (wcschr(mode, L'w')) {
        access |= GENERIC_WRITE;
        creation = CREATE_ALWAYS;
    }
    if (wcschr(mode, L'a')) {
        access |= FILE_APPEND_DATA;
        creation = OPEN_ALWAYS;
    }
    if (wcschr(mode, L'+') || wcschr(&mode[1], L'+')) {
        access |= GENERIC_READ | GENERIC_WRITE;
    }

    HANDLE file = CreateFileW(filename, access, shareMode, NULL, creation, FILE_ATTRIBUTE_NORMAL, NULL);
    return (FILE*)(file != INVALID_HANDLE_VALUE ? file : NULL);
}

extern "C" int __cdecl fclose(FILE * file) {
    return CloseHandle((HANDLE)(file)) ? 0: -1;
}

extern "C" size_t __cdecl fwrite(const void* buffer, size_t size, size_t count, FILE * file) {
    if (!file || !buffer || size == 0 || count == 0) {
        return 0;
    }

    DWORD bytesToWrite = static_cast<DWORD>(size * count);
    DWORD bytesWritten = 0;

    BOOL success = WriteFile((HANDLE)file, buffer, bytesToWrite, &bytesWritten, NULL);

    if (!success) {
        return 0;
    }

    // Return the number of elements (count) successfully written
    return bytesWritten / size;
}

extern "C" char* __cdecl
fgets(char* str, int n, FILE* file)
{
    int count = 0;
    CHAR ch;
    DWORD bytesread;

    while ((count + 1) < n && ReadFile((HANDLE)file, &ch, sizeof(ch), &bytesread, NULL) && bytesread == sizeof(ch)) {
        str[count] = ch;
        count++;
        if (ch == '\n' || ch == '\r') {
            break;
        }
    }
    str[count] = '\0';
    if (count == 0) {
        return NULL;
    }
    return str;
}

extern "C" wchar_t* __cdecl
fgetws(wchar_t* str, int n, FILE * file)
{
    int count = 0;
    CHAR ch;
    DWORD bytesread;

    while ((count + 1) < n && ReadFile((HANDLE)file, &ch, sizeof(ch), &bytesread, NULL) && bytesread == sizeof(ch)) {
        str[count] = ch;
        count++;
        if (ch == '\n' || ch == '\r') {
            break;
        }
    }
    str[count] = '\0';
    if (count == 0) {
        return NULL;
    }
    return str;
}

extern "C" int __cdecl fseek(FILE * file, long offset, int origin) {
    DWORD moveMethod;
    switch (origin) {
    case SEEK_SET:  // Set file pointer to `offset` bytes from the beginning
        moveMethod = FILE_BEGIN;
        break;
    case SEEK_CUR:  // Set file pointer to `offset` bytes from the current position
        moveMethod = FILE_CURRENT;
        break;
    case SEEK_END:  // Set file pointer to `offset` bytes from the end of the file
        moveMethod = FILE_END;
        break;
    default:        // Invalid origin
        return -1;
    }

    // Move the file pointer and check for errors
    if (SetFilePointer((HANDLE)file, offset, NULL, moveMethod) == INVALID_SET_FILE_POINTER) {
        if (GetLastError() != NO_ERROR) {
            return -1; // Return error if the pointer could not be set
        }
    }
    return 0; // Success
}

extern "C" int __cdecl remove(const char* filename) {
    // Use DeleteFileA to delete the file specified by filename
    if (DeleteFileA(filename) != 0) {
        return 0; // Success
    }
    else {
        return -1; // Failure, file could not be deleted
    }
}

extern "C" int __cdecl _wremove(const wchar_t* filename) {
    // Use DeleteFileW to delete the file specified by filename (wide char version)
    if (DeleteFileW(filename) != 0) {
        return 0; // Success
    }
    else {
        return -1; // Failure, file could not be deleted
    }
}

extern "C" int __cdecl rename(const char* oldname, const char* newname) {
    if (MoveFileA(oldname, newname) != 0) {
        return 0; // Success
    }
    else {
        return -1; // Failure
    }
}

extern "C" int __cdecl _wrename(const wchar_t* oldname, const wchar_t* newname) {
    if (MoveFileW(oldname, newname) != 0) {
        return 0; // Success
    }
    else {
        return -1; // Failure
    }
}

extern "C" int __cdecl fflush(FILE * file) {
    if (!file) {
        return EOF; // Invalid file pointer
    }

    // Flush the file buffers
    if (!FlushFileBuffers((HANDLE)file)) {
        return EOF; // Flush failed
    }

    return 0; // Success
}

extern "C" size_t __cdecl fread(void* buffer, size_t size, size_t count, FILE * file) {
    if (!file || !buffer || size == 0 || count == 0) {
        return 0;
    }

    DWORD bytesToRead = static_cast<DWORD>(size * count);
    DWORD bytesRead = 0;

    BOOL success = ReadFile((HANDLE)file, buffer, bytesToRead, &bytesRead, NULL);

    if (!success) {
        return 0;
    }

    // Return the number of elements (count) successfully read
    return bytesRead / size;
}

extern "C" long __cdecl ftell(FILE * file) {
    if (!file) {
        return -1;
    }

    DWORD position = SetFilePointer((HANDLE)file, 0, NULL, FILE_CURRENT);
    if (position == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR) {
        return -1;
    }

    return static_cast<long>(position);
}