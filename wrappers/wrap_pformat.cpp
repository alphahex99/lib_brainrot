#include <stdarg.h>

#include "translators/translate.hpp"

extern "C" int __cdecl __real_pformat(int flags, void *dest, int max, const char *fmt, va_list argv);

extern "C" int __cdecl __wrap_pformat(int flags, void *dest, int max, const char *fmt, va_list argv)
{
    std::string str{fmt};

    if (translate(str))
    {
        return __real_pformat(flags, dest, max, str.c_str(), argv);
    }
    else
    {
        return __real_pformat(flags, dest, max, fmt, argv);
    }
}
