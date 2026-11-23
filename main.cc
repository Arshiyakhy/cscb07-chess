#include <iostream>
#include <string>
#include "controller.h"

int main(int argc, char *argv[])
{
    bool colour = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-colour" || arg == "-color")
            colour = true;
    }

    Controller c{std::cout, colour};
    c.run(std::cin);
    return 0;
}