#include <stdarg.h>

#include "translators/my_pformat.h"

extern "C" int __cdecl __real_pformat(int flags, void *dest, int max, const char *fmt, va_list argv);

extern "C" int __cdecl __wrap_pformat(int flags, void *dest, int max, const char *fmt, va_list argv)
{
    return my_pformat(__real_pformat, flags, dest, max, fmt, argv);
}
