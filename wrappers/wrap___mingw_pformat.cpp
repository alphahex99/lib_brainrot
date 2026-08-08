#include <stdarg.h>

#include "translators/my_pformat.h"

extern "C" int __cdecl __real___mingw_pformat(int flags, void *dest, int max, const char *fmt, va_list argv);

extern "C" int __cdecl __wrap___mingw_pformat(int flags, void *dest, int max, const char *fmt, va_list argv)
{
    return my_pformat(__real___mingw_pformat, flags, dest, max, fmt, argv);
}
