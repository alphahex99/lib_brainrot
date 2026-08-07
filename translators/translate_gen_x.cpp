#include "translate_gen_x.hpp"

#include <regex>

bool translate_gen_x(std::string &str)
{
    // str = std::regex_replace(str, std::regex("hello", std::regex_constants::icase), "whazzup");
    str = std::regex_replace(str, std::regex("Hello"), "Whazzup");
    str = std::regex_replace(str, std::regex("hello"), "whazzup");

    str = std::regex_replace(str, std::regex("\\b6\\s+7"), "6-7!!");

    return true;
}
