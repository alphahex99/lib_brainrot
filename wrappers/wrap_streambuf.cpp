#include "wrap_streambuf.hpp"

#include <string>

#include "translators/translate_gen_x.hpp"

wrap_streambuf::wrap_streambuf(std::ostream &real_cout) : real_cout(real_cout), real_streambuf(real_cout.rdbuf())
{
    real_cout.rdbuf(this);
}

wrap_streambuf::~wrap_streambuf()
{
    flush();
    real_cout.rdbuf(real_streambuf);
}

int wrap_streambuf::sync()
{
    flush();
    return real_streambuf->pubsync();
}

// https://en.cppreference.com/cpp/io/basic_streambuf/sputn
//
std::streamsize wrap_streambuf::xsputn(const char *s, std::streamsize count)
{
    buf.append(s, static_cast<std::size_t>(count));
    return count;
}

// https://en.cppreference.com/cpp/io/basic_streambuf/overflow
//
wrap_streambuf::int_type wrap_streambuf::overflow(int_type ch)
{
    if (!traits_type::eq_int_type(ch, traits_type::eof()))
    {
        buf += traits_type::to_char_type(ch);
    }

    flush();
    return traits_type::not_eof(ch);
}

void wrap_streambuf::flush()
{
    if (buf.empty())
    {
        return;
    }

    // TODO: in/out, keep original text for fallback?
    (void) translate_gen_x(buf);

    // TODO: we're double buffering here for no reason
    real_streambuf->sputn(buf.data(), static_cast<std::streamsize>(buf.size()));

    buf.clear();
}
