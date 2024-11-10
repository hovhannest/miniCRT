#pragma once
#include <cassert>
#include <cstdio>
#include <cstring>

void test_memcpy() {
    char src[] = "Hello, memcpy!";
    char dest[20] = {};

    memcpy(dest, src, strlen(src) + 1);
    assert(strcmp(dest, src) == 0);
    printf("test_memcpy passed\n");
}

void test_memmove() {
    char buffer[] = "Hello, memmove!";
    memmove(buffer + 7, buffer, 5);  // Moving "Hello" to overlap

    assert(strcmp(buffer, "Hello, Hellove!") == 0);
    printf("test_memmove passed\n");
}

void test_memset() {
    char buffer[20];
    memset(buffer, 'A', 10);
    buffer[10] = '\0';

    assert(strcmp(buffer, "AAAAAAAAAA") == 0);
    printf("test_memset passed\n");
}

void test_memcmp() {
    char buf1[] = "abcdef";
    char buf2[] = "abcdef";
    char buf3[] = "abcdeg";

    assert(memcmp(buf1, buf2, 6) == 0);     // buf1 and buf2 are identical
    assert(memcmp(buf1, buf3, 6) < 0);      // buf1 is less than buf3
    assert(memcmp(buf3, buf1, 6) > 0);      // buf3 is greater than buf1
    printf("test_memcmp passed\n");
}