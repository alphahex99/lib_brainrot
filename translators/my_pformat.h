#ifndef _MY_VPRINTF_H
#define _MY_VPRINTF_H

#include <stdarg.h>
#include <stdio.h>

typedef int(real_pformat_fn)(int, void *, int, const char *, va_list);

#ifdef __cplusplus
extern "C"
{
#endif

    int __cdecl my_pformat(real_pformat_fn *real_pformat, int flags, void *dest, int max, const char *fmt,
                           va_list argv);

#ifdef __cplusplus
}
#endif

#endif /* _MY_VPRINTF_H */
