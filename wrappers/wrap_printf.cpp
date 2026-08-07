#include <stdarg.h>
#include <stdio.h>
#include <string>

#include "translate_test.hpp"

extern "C" int __real_printf(const char *, ...);

extern "C" int __wrap_printf(const char *format, ...)
{
    va_list args;

    va_start(args, format);

    std::string str{format};

    translate_test(str);

    int result = vprintf(str.c_str(), args);

    va_end(args);

    return result;
}
