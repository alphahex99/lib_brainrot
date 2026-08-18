#include "translate.hpp"

#include "translate_gen_x.hpp"
#include "translate_owo.hpp"

static void puts_error(std::string &str)
{
    for (std::string::size_type pos = 0; (pos = str.find("\n", pos)) != std::string::npos; pos += 2)
    {
        str.replace(pos, 1, "\\n");
    }

    str = "-- Parse error: \"" + str + "\"\n";

    fputs(str.c_str(), stderr);
}

bool translate(std::string &str)
{
    std::string str_original = str;

    // TODO: some way to pick between them
    if (translate_owo(str))
    {
        return true;
    }
    else
    {
        puts_error(str_original);
        return false;
    }
}
