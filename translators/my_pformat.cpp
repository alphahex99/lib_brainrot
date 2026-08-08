#include "my_pformat.h"

#include <string>

#include "translate_gen_x.hpp"

static void puts_error(const char *__restrict__ _Format)
{
    std::string str{_Format};

    for (std::string::size_type pos = 0; (pos = str.find("\n", pos)) != std::string::npos; pos += 2)
    {
        str.replace(pos, 1, "\\n");
    }

    str = "-- Parse error: \"" + str + "\"\n";

    fputs(str.c_str(), stderr);
}

int __cdecl my_pformat(real_pformat_fn *real_pformat, int flags, void *dest, int max, const char *fmt, va_list argv)
{
    std::string str_format{fmt};

    if (translate_gen_x(str_format))
    {
        return real_pformat(flags, dest, max, str_format.c_str(), argv);
    }
    else
    {
        puts_error(fmt);
        return real_pformat(flags, dest, max, fmt, argv);
    }
}
