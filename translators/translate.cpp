#include "translate.hpp"

#include "translate_gen_x.hpp"

static void puts_error(const char *__restrict__ fmt)
{
    std::string str{fmt};

    for (std::string::size_type pos = 0; (pos = str.find("\n", pos)) != std::string::npos; pos += 2)
    {
        str.replace(pos, 1, "\\n");
    }

    str = "-- Parse error: \"" + str + "\"\n";

    fputs(str.c_str(), stderr);
}

bool translate(std::string &str, const char *original_fmt)
{
    // TODO: some way to pick between them
    if (translate_gen_x(str))
    {
        return true;
    }
    else
    {
        puts_error(original_fmt);
        return false;
    }
}
