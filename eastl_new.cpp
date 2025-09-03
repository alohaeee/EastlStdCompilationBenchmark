#ifdef USE_EASTL
// Simple implementation of EASTL required new/delete operators and functions
#include <new>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>

// Required by EASTL
void* operator new[](size_t size, const char* /*name*/, int /*flags*/, 
                     unsigned /*debugFlags*/, const char* /*file*/, int /*line*/) {
    return malloc(size);
}

void* operator new[](size_t size, size_t /*alignment*/, size_t /*alignmentOffset*/,
                     const char* /*name*/, int /*flags*/, unsigned /*debugFlags*/,
                     const char* /*file*/, int /*line*/) {
    return malloc(size);
}

// Required by EASTL string formatting
namespace EA {
    namespace StdC {
        int Vsnprintf(char* pDestination, size_t n, const char* pFormat, va_list arguments) {
            return vsnprintf(pDestination, n, pFormat, arguments);
        }
    }
}
#endif