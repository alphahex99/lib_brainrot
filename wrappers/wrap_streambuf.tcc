#ifndef _WRAP_STREAMBUF_TCC
#define _WRAP_STREAMBUF_TCC

#include <string>

#include "translators/translate.hpp"

template <typename CharT, typename Traits>
wrap_streambuf<CharT, Traits>::wrap_streambuf(ostream_type &real_cout)
    : real_cout(real_cout), real_streambuf(real_cout.rdbuf())
{
    // initial pointer values
    this->setp(buffer, buffer + buffer_size);

    // redirect to our streambuf
    real_cout.rdbuf(this);
}

template <typename CharT, typename Traits> wrap_streambuf<CharT, Traits>::~wrap_streambuf()
{
    // flush
    this->pubsync();

    // restore original streambuf
    real_cout.rdbuf(real_streambuf);
}

// https://en.cppreference.com/cpp/io/basic_streambuf/pubsync
//
template <typename CharT, typename Traits> int wrap_streambuf<CharT, Traits>::sync()
{
    const std::streamsize count = this->pptr() - this->pbase();
    if (count > 0)
    {
        std::basic_string<CharT> str(this->pbase(), static_cast<std::size_t>(count));

        // TODO: wstring support? + wpformat hook
        if (translate(str))
        {
            if (real_streambuf->sputn(str.data(), static_cast<std::streamsize>(str.size())) !=
                static_cast<std::streamsize>(str.size()))
            {
                return -1;
            }
        }
        else
        {
            if (real_streambuf->sputn(this->pbase(), count) != count)
            {
                return -1;
            }
        }
    }

    // update pointer values
    this->setp(buffer, buffer + buffer_size);

    // flush
    return real_streambuf->pubsync();
}

// https://en.cppreference.com/cpp/io/basic_streambuf/sputn
//
template <typename CharT, typename Traits>
std::streamsize wrap_streambuf<CharT, Traits>::xsputn(const char_type *s, std::streamsize count)
{
    std::streamsize i = 0;

    for (; i < count; ++i)
    {
        if (this->pptr() == this->epptr())
        {
            if (sync() != 0)
            {
                break;
            }
        }

        *this->pptr() = s[i];
        this->pbump(1);

        if ((s[i] == newline) && (sync() != 0))
        {
            ++i;
            break;
        }
    }

    return i;
}

// https://en.cppreference.com/cpp/io/basic_streambuf/overflow
//
template <typename CharT, typename Traits>
typename wrap_streambuf<CharT, Traits>::int_type wrap_streambuf<CharT, Traits>::overflow(int_type ch)
{
    if (traits_type::eq_int_type(ch, traits_type::eof()))
    {
        return sync() == 0 ? traits_type::not_eof(ch) : traits_type::eof();
    }

    if ((this->pptr() == this->epptr()) && (sync() != 0))
    {
        return traits_type::eof();
    }

    *this->pptr() = traits_type::to_char_type(ch);
    this->pbump(1);

    if ((traits_type::to_char_type(ch) == newline) && (sync() != 0))
    {
        return traits_type::eof();
    }

    return traits_type::not_eof(ch);
}

#endif /* _WRAP_STREAMBUF_TCC */
