#include <stdarg.h>
#include <stdio.h>

extern "C" int __real_printf(const char *, ...);

extern "C" int __wrap_printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    __real_printf("[!] ");

    int result = vprintf(format, args);

    va_end(args);

    return result;
}
