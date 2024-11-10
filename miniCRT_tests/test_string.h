#pragma once
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cwchar>

void test_atoi() {
    assert(atoi("1234") == 1234);
    assert(atoi("0") == 0);
    assert(atoi("999") == 999);
    assert(atoi("00123") == 123);  // Leading zeros should be ignored
    assert(atoi("") == 0);  // Empty string should return 0
    printf("test_atoi passed\n");
}

void test_wtoi() {
    assert(_wtoi(L"1234") == 1234);
    assert(_wtoi(L"0") == 0);
    assert(_wtoi(L"999") == 999);
    assert(_wtoi(L"00123") == 123);  // Leading zeros should be ignored
    assert(_wtoi(L"") == 0);  // Empty string should return 0
    printf("test_wtoi passed\n");
}

void test_strcat_s() {
    char buffer[50] = "Hello, ";
    assert(strcat_s(buffer, sizeof(buffer), "World!") == 0);
    assert(strcmp(buffer, "Hello, World!") == 0);  // Check if the result is correct
    strcat_s(buffer, sizeof(buffer), " How are you?");
    assert(strcmp(buffer, "Hello, World! How are you?") == 0);  // Check concatenation with larger string
    printf("test_strcat_s passed\n");
}

void test_wcscat_s() {
    wchar_t buffer[50] = L"Hello, ";
    assert(wcscat_s(buffer, sizeof(buffer) / sizeof(wchar_t), L"World!") == 0);
    assert(wcscmp(buffer, L"Hello, World!") == 0);  // Check if the result is correct
    wcscat_s(buffer, sizeof(buffer) / sizeof(wchar_t), L" How are you?");
    assert(wcscmp(buffer, L"Hello, World! How are you?") == 0);  // Check concatenation with larger string
    printf("test_wcscat_s passed\n");
}

void test_strncat() {
    char buffer[50] = "Hello, ";
    assert(strcmp(strncat(buffer, "World!", 3), "Hello, Wor") == 0);  // Should concatenate only 3 chars
    assert(strcmp(strncat(buffer, "ld!", 2), "Hello, World") == 0);  // Should concatenate 2 more chars
    printf("test_strncat passed\n");
}

void test_wcsncat() {
    wchar_t buffer[50] = L"Hello, ";
    assert(wcscmp(wcsncat(buffer, L"World!", 3), L"Hello, Wor") == 0);  // Should concatenate only 3 chars
    assert(wcscmp(wcsncat(buffer, L"ld!", 2), L"Hello, World") == 0);  // Should concatenate 2 more chars
    printf("test_wcsncat passed\n");
}

void test_strchr() {
    const char* str = "Hello, World!";
    assert(strchr(str, 'o') == str + 4);  // First 'o' at index 4
    assert(strchr(str, 'W') == str + 7);  // 'W' at index 7
    assert(strchr(str, 'z') == nullptr);  // 'z' does not exist
    printf("test_strchr passed\n");
}

void test_wcschr() {
    const wchar_t* str = L"Hello, World!";
    assert(wcschr(str, L'o') == str + 4);  // First 'o' at index 4
    assert(wcschr(str, L'W') == str + 7);  // 'W' at index 7
    assert(wcschr(str, L'z') == nullptr);  // 'z' does not exist
    printf("test_wcschr passed\n");
}

void test_strlen() {
    assert(strlen("Hello") == 5);
    assert(strlen("12345") == 5);
    assert(strlen("") == 0);  // Empty string
    assert(strlen("a") == 1);  // Single character
    printf("test_strlen passed\n");
}

void test_wcslen() {
    assert(wcslen(L"Hello") == 5);
    assert(wcslen(L"12345") == 5);
    assert(wcslen(L"") == 0);  // Empty string
    assert(wcslen(L"a") == 1);  // Single character
    printf("test_wcslen passed\n");
}

void test_strstr() {
    const char* str = "Hello, World!";
    assert(strstr(str, "World") == str + 7);  // Should find "World"
    assert(strstr(str, "lo") == str + 3);  // Should find "lo"
    assert(strstr(str, "abc") == nullptr);  // Not found
    printf("test_strstr passed\n");
}

void test_wcsstr() {
    const wchar_t* str = L"Hello, World!";
    assert(wcsstr(str, L"World") == str + 7);  // Should find "World"
    assert(wcsstr(str, L"lo") == str + 3);  // Should find "lo"
    assert(wcsstr(str, L"abc") == nullptr);  // Not found
    printf("test_wcsstr passed\n");
}

void test_toupper() {
    assert(toupper('a') == 'A');
    assert(toupper('z') == 'Z');
    assert(toupper('A') == 'A');  // Already uppercase
    assert(toupper('1') == '1');  // Non-alphabetic should remain unchanged
    printf("test_toupper passed\n");
}

void test_towupper() {
    assert(towupper(L'a') == L'A');
    assert(towupper(L'z') == L'Z');
    assert(towupper(L'A') == L'A');  // Already uppercase
    assert(towupper(L'1') == L'1');  // Non-alphabetic should remain unchanged
    printf("test_towupper passed\n");
}

void test_strtok_s() {
    char str[] = "Hello, World, how, are, you!";
    char* context = nullptr;
    char* token = strtok_s(str, ",", &context);
    assert(strcmp(token, "Hello") == 0);
    token = strtok_s(nullptr, ",", &context);
    assert(strcmp(token, " World") == 0);
    token = strtok_s(nullptr, ",", &context);
    assert(strcmp(token, " how") == 0);
    printf("test_strtok_s passed\n");
}

void test_wcstok_s() {
    wchar_t str[] = L"Hello, World, how, are, you!";
    wchar_t* context = nullptr;
    wchar_t* token = wcstok_s(str, L",", &context);
    assert(wcscmp(token, L"Hello") == 0);
    token = wcstok_s(nullptr, L",", &context);
    assert(wcscmp(token, L" World") == 0);
    token = wcstok_s(nullptr, L",", &context);
    assert(wcscmp(token, L" how") == 0);
    printf("test_wcstok_s passed\n");
}
