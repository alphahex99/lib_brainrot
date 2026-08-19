Just playing around with `-Wl,--wrap`

Originally compile-time XORing experiments, but I got bored. See 2nd commit, hash: `157713d`

*Forgive me father for I have sinned*

---

```cpp
#include <iostream>
#include <stdio.h>

int main()
{
    printf("Hello World!\n");
    printf("1 2 3 4 5 6 7 8 9\n");
    printf("The quick brown fox jumps over the lazy dog\n\n");

    std::cout << "Hello World!\n";
    std::cout << "1 2 3 4 5 6 7 8 9\n";
    std::cout << "The quick brown fox jumps over the lazy dog\n\n";

    return 0;
}
```

```
 *  Executing task: ./build/brainrot.exe 

Hewwo w-world!
1 2 3 4 5 6-7!! 8 9
The quick bwown fox jumps over the wazy dog

Hewwo w-world!
1 2 3 4 5 6-7!! 8 9
The quick bwown fox jumps over the wazy dog

 *  Terminal will be reused by tasks, press any key to close it.
```