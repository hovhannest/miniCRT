#pragma once

#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include <assert.h>

void test_wprintf() {
    wprintf(L"Test wprintf: %d, %s, %f\n", 42, L"Hello, world!", 3.14159);
}

void test_fwprintf() {
    FILE* file = fopen("fwprintf_test.txt", "w");
    if (file != NULL) {
        fwprintf(file, L"Test fwprintf: %d, %s, %f\n", 42, L"Hello, file!", 3.14159);
        fclose(file);
    }
}

void test_swprintf() {
    wchar_t buffer[100];
    swprintf_s(buffer, sizeof(buffer) / sizeof(wchar_t), L"Test swprintf: %d, %s, %f", 42, L"Hello, buffer!", 3.14159);
    swprintf(buffer, L"Test swprintf: %d, %s, %f", 42, L"Hello, buffer!", 3.14159);
    wprintf(L"%s\n", buffer);
}