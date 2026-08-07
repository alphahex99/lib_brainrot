#include <stdarg.h>
#include <stdio.h>
#include <string>

#include "translate_gen_x.hpp"

#define __dbg_printf(format, ...) __real_printf(format, ##__VA_ARGS__)

extern "C" int __real_printf(const char *, ...);

extern "C" int __wrap_printf(const char *format, ...)
{
    int result;

    va_list args;
    va_start(args, format);

    std::string str_format{format};

    if (translate_gen_x(str_format))
    {
        result = vprintf(str_format.c_str(), args);
    }
    else
    {
        result = vprintf(format, args);

        std::string str_errmsg{format};
        for (std::string::size_type i = 0; (i = str_errmsg.find("\n", i)) != std::string::npos; i++)
        {
            str_errmsg.replace(i, 2, "\\n");
        }
        __dbg_printf("-- Parse error: \"%s\"\n", str_errmsg.c_str());
    }

    va_end(args);

    return result;
}
