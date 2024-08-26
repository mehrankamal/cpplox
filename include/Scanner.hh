#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "Token.hh"

namespace Lox
{
    class Scanner
    {
        std::string source;
        std::vector<Token> tokens;
        int start = 0;
        int current = 0;
        int line = 1;

        bool is_at_end();
        void scan_token();
        char advance();
        void add_token(TokenType type);
        void add_token(TokenType type, std::optional<std::any> literal);
        bool match(char expected);
        char peek();
        char peek_next();
        bool is_digit(char c);
        bool is_alpha(char c);
        bool is_alpha_numeric(char c);

        void string();
        void number();
        void identifier();

        std::map<std::string, TokenType> keywords = std::map<std::string, TokenType>({
            std::pair<std::string, TokenType>({"and", TokenType::AND}),
            std::pair<std::string, TokenType>({"class", TokenType::CLASS}),
            std::pair<std::string, TokenType>({"else", TokenType::ELSE}),
            std::pair<std::string, TokenType>({"false", TokenType::FALSE}),
            std::pair<std::string, TokenType>({"for", TokenType::FOR}),
            std::pair<std::string, TokenType>({"fun", TokenType::FUN}),
            std::pair<std::string, TokenType>({"if", TokenType::IF}),
            std::pair<std::string, TokenType>({"nil", TokenType::NIL}),
            std::pair<std::string, TokenType>({"or", TokenType::OR}),
            std::pair<std::string, TokenType>({"print", TokenType::PRINT}),
            std::pair<std::string, TokenType>({"return", TokenType::RETURN}),
            std::pair<std::string, TokenType>({"super", TokenType::SUPER}),
            std::pair<std::string, TokenType>({"this", TokenType::THIS}),
            std::pair<std::string, TokenType>({"true", TokenType::TRUE}),
            std::pair<std::string, TokenType>({"var", TokenType::VAR}),
            std::pair<std::string, TokenType>({"while", TokenType::WHILE}),
        });

    public:
        Scanner(std::string source);
        std::vector<Token> scan_tokens();
    };
}