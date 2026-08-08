#ifndef _WRAP_STREAMBUF_HPP
#define _WRAP_STREAMBUF_HPP

#include <cstddef>
#include <ostream>
#include <streambuf>

template <typename CharT, typename Traits = std::char_traits<CharT>>
class wrap_streambuf : public std::basic_streambuf<CharT, Traits>
{
    using base_type = std::basic_streambuf<CharT, Traits>;

  public:
    using char_type = typename base_type::char_type;
    using int_type = typename base_type::int_type;
    using traits_type = typename base_type::traits_type;

    using ostream_type = std::basic_ostream<CharT, Traits>;
    using streambuf_type = std::basic_streambuf<CharT, Traits>;

    explicit wrap_streambuf(ostream_type &real_cout);
    ~wrap_streambuf() override;

  protected:
    int sync() override;
    std::streamsize xsputn(const char_type *s, std::streamsize count) override;
    int_type overflow(int_type ch = traits_type::eof()) override;

  private:
    // TODO: somehow inherit the size from std::cout?
    static constexpr std::size_t buffer_size = 4096;
    char_type buffer[buffer_size];

    static constexpr char_type newline = CharT{'\n'};

    ostream_type &real_cout;
    streambuf_type *real_streambuf;
};

#include "wrap_streambuf.tcc"

#endif // _WRAP_STREAMBUF_HPP
