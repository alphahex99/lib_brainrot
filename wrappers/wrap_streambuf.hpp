#ifndef _WRAP_STREAMBUF_HPP
#define _WRAP_STREAMBUF_HPP

#include <ostream>
#include <streambuf>

class wrap_streambuf : public std::streambuf
{
  public:
    explicit wrap_streambuf(std::ostream &real_cout);
    ~wrap_streambuf() override;

  protected:
    int sync() override;

    std::streamsize xsputn(const char *s, std::streamsize count) override;
    int_type overflow(int_type ch = traits_type::eof()) override;

  private:
    std::string buf;

    std::ostream &real_cout;
    std::streambuf *real_streambuf;

    void flush();
};

#endif /* _WRAP_STREAMBUF_HPP */
