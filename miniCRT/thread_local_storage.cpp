
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#include <limits.h>
// _tls_index equivalent using Windows TLS API
extern "C" DWORD _tls_index = 0;

// _Init_thread_header - Initialize thread-specific data (TLS)
extern "C" void __cdecl _Init_thread_header(int* const pOnce) {
    // Allocate a TLS index for the thread if not already done
    if (_tls_index == TLS_OUT_OF_INDEXES) {
        _tls_index = TlsAlloc();
        if (_tls_index == TLS_OUT_OF_INDEXES) {
            return;
        }
    }

    // Initialize thread-specific data or perform any custom initialization here
    int* thread_data = new int(0);  // Example: Allocating memory for thread-specific data
    if (!TlsSetValue(_tls_index, thread_data)) {
    }
}

// _Init_thread_footer - Clean up thread-specific data (TLS)
extern "C" void __cdecl _Init_thread_footer(int* const pOnce) noexcept {
    int* thread_data = static_cast<int*>(TlsGetValue(_tls_index));
    if (thread_data) {
        // Cleanup thread-specific data
        delete thread_data;
        TlsSetValue(_tls_index, nullptr);
    }
}

int _Init_thread_epoch = INT_MIN;
