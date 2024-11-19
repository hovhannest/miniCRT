#pragma once
#include <Windows.h>
#include <cstdio>
#include <cassert>
#include <cstring>

void test_fopen_read() {
    const char* filename = "test_read.txt";

    // Create file for testing
    HANDLE file = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(file != INVALID_HANDLE_VALUE);
    CloseHandle(file);

    FILE* f = fopen(filename, "r");
    assert(f != NULL);  // Check if file is opened successfully for reading
    assert(fclose(f) == 0);  // Ensure the file closes correctly
    printf("test_fopen_read passed\n");
}

void test_fopen_write() {
    const char* filename = "test_write.txt";

    FILE* f = fopen(filename, "w");
    assert(f != NULL);  // Check if file is opened successfully for writing

    // Write to the file
    const char* data = "Test writing data";
    fwrite(data, 1, strlen(data), f);

    assert(fclose(f) == 0);  // Ensure the file closes correctly

    // Verify that file was created and written to
    HANDLE fileHandle = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(fileHandle != INVALID_HANDLE_VALUE);
    CloseHandle(fileHandle);

    printf("test_fopen_write passed\n");
}

void test_fopen_append() {
    const char* filename = "test_append.txt";

    // Create file and write initial content
    FILE* f = fopen(filename, "w");
    assert(f != NULL);
    const char* initialData = "Initial content";
    fwrite(initialData, 1, strlen(initialData), f);
    assert(fclose(f) == 0);

    // Open the file for appending
    f = fopen(filename, "a");
    assert(f != NULL);  // Check if file is opened successfully for appending

    const char* appendedData = "Appended data";
    fwrite(appendedData, 1, strlen(appendedData), f);

    assert(fclose(f) == 0);  // Ensure the file closes correctly

    // Check if the file size has increased (basic check for appending)
    HANDLE fileHandle = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    assert(fileHandle != INVALID_HANDLE_VALUE);
    DWORD fileSize = GetFileSize(fileHandle, NULL);
    assert(fileSize > strlen(initialData));  // File size should be larger than the initial data size
    CloseHandle(fileHandle);

    printf("test_fopen_append passed\n");
}

void test_fopen_invalid_mode() {
    const char* filename = "test_invalid_mode.txt";

    // Try opening a file with an invalid mode
    FILE* f = fopen(filename, "z");
    assert(f == NULL);  // fopen should return NULL for unsupported modes
    printf("test_fopen_invalid_mode passed\n");
}

void test_fclose_invalid_file() {
    // Try closing an invalid file handle
    FILE* f = NULL;
    assert(fclose(f) != 0);  // Invalid file pointer should return non-zero from fclose
    printf("test_fclose_invalid_file passed\n");
}

void test_fclose_valid_file() {
    const char* filename = "test_fclose_valid.txt";

    // Create file for testing
    FILE* f = fopen(filename, "w");
    assert(f != NULL);
    assert(fclose(f) == 0);  // Ensure that fclose works for valid file handles
    printf("test_fclose_valid_file passed\n");
}

void test_fgets() {
    const char* test_data = "Hello, fgets!\nThis is a test.\n";
    FILE* file = fopen("test_fgets.txt", "w+");
    assert(file != NULL);

    // Write data to file and reset file pointer to beginning
    fwrite(test_data, sizeof(char), strlen(test_data), file);
    fseek(file, 0, SEEK_SET);
    fflush(file);

    char buffer[50];

    // Test fgets for the first line
    char* result = fgets(buffer, sizeof(buffer), file);
    assert(result != NULL);
    assert(strcmp(buffer, "Hello, fgets!\n") == 0);

    // Test fgets for the second line
    result = fgets(buffer, sizeof(buffer), file);
    assert(result != NULL);
    assert(strcmp(buffer, "This is a test.\n") == 0);

    // Test fgets at end of file (should return NULL)
    result = fgets(buffer, sizeof(buffer), file);
    assert(result == NULL);

    fclose(file);
    remove("test_fgets.txt");
    printf("test_fgets passed\n");
}
