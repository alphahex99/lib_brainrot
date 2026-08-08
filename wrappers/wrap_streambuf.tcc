#ifndef _WRAP_STREAMBUF_TCC
#define _WRAP_STREAMBUF_TCC

#include <string>

#include "translators/translate_gen_x.hpp"

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
        std::string str(this->pbase(), static_cast<std::size_t>(count));

        if (translate_gen_x(str))
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

    // success! update pointer values
    this->setp(buffer, buffer + buffer_size);

    // flush
    return real_streambuf->pubsync();
}

// https://en.cppreference.com/cpp/io/basic_streambuf/overflow
//
template <typename CharT, typename Traits>
typename wrap_streambuf<CharT, Traits>::int_type wrap_streambuf<CharT, Traits>::overflow(int_type ch)
{
    if (sync() != 0)
    {
        return traits_type::eof();
    }

    if (!traits_type::eq_int_type(ch, traits_type::eof()))
    {
        *this->pptr() = traits_type::to_char_type(ch);
        this->pbump(1);
    }

    return traits_type::not_eof(ch);
}

#endif /* _WRAP_STREAMBUF_TCC */
