#include "translate_owo.hpp"

#include <regex>

bool translate_owo(std::string &str)
{
    str = std::regex_replace(str, std::regex(" m", std::regex_constants::icase), " m-m");
    str = std::regex_replace(str, std::regex("r([aeiou])", std::regex_constants::icase), "w$1");
    str = std::regex_replace(str, std::regex(" w", std::regex_constants::icase), " w-w");

    std::regex re("([ aeiou])(l+)([aeiou])", std::regex_constants::icase);
    for (std::smatch sm; std::regex_search(str, sm, re);)
    {
        str.replace(sm.position(), sm.length(), sm[1].str() + std::string(sm[2].length(), 'w') + sm[3].str());
    }

    return true;
}
