#ifndef _CRYPT_HPP
#define _CRYPT_HPP

#include <string>

#define CRYPT(chr)   (chr + 1)
#define DECRYPT(chr) (chr - 1)

template <const size_t len> constexpr const char *crypt(const char (&str_plaintext)[len])
{
    std::string str_obfuscated{str_plaintext};

    for (size_t i = 0; i < len; i++)
    {
        str_obfuscated[i] = CRYPT(str_obfuscated[i]);
    }

    return str_obfuscated.c_str();
}

inline __attribute__((always_inline)) void decrypt(char *__restrict__ out_buf, const char *__restrict__ str_obfuscated)
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

#endif /* _CRYPT_HPP */
