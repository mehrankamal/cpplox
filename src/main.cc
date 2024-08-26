#include <iostream>
#include <optional>
#include <fstream>

#include "Lox.hh"

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        std::cout << "Usage ./Lox [script]" << std::endl;
        exit(64);
    }
    else if (argc == 2)
    {
        Lox::run_file(argv[1]);
    }
    else
    {
        Lox::run_prompt();
    }

    return 0;
}
