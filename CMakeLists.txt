cmake_minimum_required(VERSION 3.11)

project(EASTL)

# Define custom build type RelDebug
set(CMAKE_CONFIGURATION_TYPES Debug Release MinSizeRel RelWithDebInfo RelDebug CACHE STRING "Available build types" FORCE)

string(REGEX REPLACE "/EH[a-z]+" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
STRING (REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

# Add the EASTL submodule
add_subdirectory(EASTL)

# Set flags for the custom build type RelDebug
set(CMAKE_CXX_FLAGS_RELDEBUG "${CMAKE_CXX_FLAGS_MINSIZEREL}")
set(CMAKE_C_FLAGS_RELDEBUG "${CMAKE_C_FLAGS_MINSIZEREL}")
set(CMAKE_EXE_LINKER_FLAGS_RELDEBUG "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL}")
set(CMAKE_SHARED_LINKER_FLAGS_RELDEBUG "${CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL}")

# Set compile options for EASTL
target_compile_options(EASTL PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/GR->          # Disable RTTI
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/MT>  # Statically linked runtime for Release
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:MinSizeRel>>:/MT>  # Statically linked runtime for Release
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelWithDebInfo>>:/MT>  # Statically linked runtime for Release
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/MTd>   # Statically linked runtime for Debug
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelDebug>>:/MTd>   # Statically linked runtime for Debug
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelDebug>>:/O1>   # Statically linked runtime for Debug
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelDebug>>:/Ob1>   # Statically linked runtime for Debug
    $<$<CXX_COMPILER_ID:MSVC>:/D_NO_CRT_STDIO_INLINE> # Define _NO_CRT_STDIO_INLINE
)

# Set output directories based on architecture and configuration
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH_DIR "x64")
else()
    set(ARCH_DIR "Win32")
endif()

set_target_properties(EASTL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ARCH_DIR}/$<CONFIG>
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ARCH_DIR}/$<CONFIG>
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${ARCH_DIR}/$<CONFIG>
)

# Add custom target to build all configurations for both 32-bit and 64-bit architectures
add_custom_target(build_all
    COMMAND ${CMAKE_COMMAND} -S ${CMAKE_SOURCE_DIR} -B ${CMAKE_BINARY_DIR}/build_x64 -A x64
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x64 --config Debug
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x64 --config Release
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x64 --config MinSizeRel
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x64 --config RelWithDebInfo
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x64 --config RelDebug
    
    
    COMMAND ${CMAKE_COMMAND} -S ${CMAKE_SOURCE_DIR} -B ${CMAKE_BINARY_DIR}/build_x86 -A Win32
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x86 --config Debug
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x86 --config Release
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x86 --config MinSizeRel
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x86 --config RelWithDebInfo
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/build_x86 --config RelDebug
)