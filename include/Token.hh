#pragma once

#include <string>
#include <optional>
#include <any>
#include <ostream>

#include "TokenType.hh"

namespace Lox
{
    class Token
    {
        TokenType type;
        std::string lexeme;
        std::optional<std::any> literal;
        int line;

    public:
        Token(TokenType type, std::string lexeme, std::optional<std::any> literal, int line);
        friend std::ostream &operator<<(std::ostream &os, const Token &token);
    };
}