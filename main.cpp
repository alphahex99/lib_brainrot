#include <iostream>
#include <stdio.h>

#include "wrappers/wrap_streambuf.hpp" // TODO

int main()
{
    wrap_streambuf w{std::cout}; // TODO

    printf("Hello World!\n");
    printf("1 2 3 4 5 6 7 8 9\n");
    printf("The quick brown fox jumps over the lazy dog\n\n");

    std::cout << "Hello World!\n";
    std::cout << "1 2 3 4 5 6 7 8 9\n";
    std::cout << "The quick brown fox jumps over the lazy dog\n\n";

    return 0;
}
