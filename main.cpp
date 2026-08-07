#include <stdio.h>
#include <string>

#define ALWAYS_INLINE // inline __attribute__((always_inline))

#define CRYPT(chr)    (chr + 1)
#define DECRYPT(chr)  (chr - 1)

template <const size_t len> constexpr const char *crypt(const char (&str_plaintext)[len])
{
    std::string str_obfuscated{str_plaintext};

    for (size_t i = 0; i < len; i++)
    {
        str_obfuscated[i] = CRYPT(str_obfuscated[i]);
    }

    return str_obfuscated.c_str();
}

ALWAYS_INLINE void decrypt(char *__restrict__ out_buf, const char *__restrict__ str_obfuscated)
{
    while (true)
    {
        *out_buf = *str_obfuscated - 1;

        if (*out_buf == '\0')
        {
            break;
        }

        out_buf++;
        str_obfuscated++;
    }
}

#define printf(_Format, ...)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        char stack_buf[sizeof(_Format)];                                                                               \
                                                                                                                       \
        decrypt(stack_buf, crypt(_Format));                                                                            \
                                                                                                                       \
        printf(stack_buf, ##__VA_ARGS__);                                                                              \
    } while (0)

int main()
{
    printf("Hello World!\n", "World");

    printf("%u%u !!!\n", 6, 7);

    return 0;
}
