#include <iostream>
#include <stdio.h>

#include "wrappers/wrap_streambuf.hpp" // TODO

int main()
{
    wrap_streambuf w{std::cout}; // TODO

    printf("Hello World!\n");
    printf("1 2 3 4 5 6 7 8 9\n");

    std::cout << "Hello World!\n";
    std::cout << "1 2 3 4 5 6 7 8 9\n";

#if 0
    // TODO: Fix flushing. Overriding xsputn was probably better...
    while (1)
        ;
#endif

    return 0;
}
