#pragma once

#include <string>

namespace Lox {
    void run_prompt();
    void run_file(char *file_path);
    void run(std::string source);
    void error(int line, std::string message);
    void report(int line, std::string where, std::string message);
}