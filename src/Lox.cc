#include <string>
#include <iostream>
#include <fstream>

#include "Lox.hh"
#include "Scanner.hh"

namespace Lox
{
    bool had_error = false;
    void run_prompt()
    {
        for (;;)
        {
            std::cout << "> ";
            std::string line;
            std::getline(std::cin, line);
            if (line.empty())
            {
                break;
            }
            run(line);
            had_error = false;
        }
    }

    void run_file(char *file_path)
    {
        std::ifstream file(file_path, std::ios::binary | std::ios::ate);
        if (!file.is_open())
        {
            std::cerr << "Could not open file: " << file_path << std::endl;
            exit(74);
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::string buffer(size, ' ');
        file.read(&buffer[0], size);
        run(buffer);
        if (had_error)
        {
            exit(65);
        }
    }

    void run(std::string source)
    {
        Lox::Scanner scanner(source);
        std::vector<Lox::Token> tokens = scanner.scan_tokens();

        for (const Lox::Token &token : tokens)
        {
            std::cout << token << std::endl;
        }
    }

    void error(int line, std::string message)
    {
        report(line, "", message);
    }

    void report(int line, std::string where, std::string message)
    {
        std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
        had_error = true;
    }

}