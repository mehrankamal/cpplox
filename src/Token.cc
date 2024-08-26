#include "Token.hh"

namespace Lox
{
    Token::Token(TokenType type, std::string lexeme, std::optional<std::any> literal, int line)
    {
        this->type = type;
        this->lexeme = lexeme;
        this->literal = literal;
        this->line = line;
    }

    std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << token.type << " " << token.lexeme << " ";
        if (token.literal.has_value())
        {
            std::any value = token.literal.value();
            if (value.type() == typeid(std::string))
            {
                os << std::any_cast<std::string>(value);
            }
            else if (value.type() == typeid(double))
            {
                os << std::any_cast<double>(value);
            }
            else if (value.type() == typeid(bool))
            {
                os << std::any_cast<bool>(value);
            }
        }
        else
        {
            os << "null";
        }
        return os;
    }
}
