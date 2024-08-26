#include <optional>

#include "Lox.hh"
#include "Scanner.hh"
#include "Token.hh"

namespace Lox
{
    Scanner::Scanner(std::string source)
    {
        this->source = source;
    }

    std::vector<Token> Scanner::scan_tokens()
    {
        while (!is_at_end())
        {
            start = current;
            scan_token();
        }

        tokens.push_back(Token(END_OF_FILE, "", std::nullopt, line));
        return tokens;
    }

    void Scanner::scan_token()
    {
        char c = advance();
        switch (c)
        {
        case '(':
            add_token(LEFT_PAREN);
            break;
        case ')':
            add_token(RIGHT_PAREN);
            break;
        case '{':
            add_token(LEFT_BRACE);
            break;
        case '}':
            add_token(RIGHT_BRACE);
            break;
        case ',':
            add_token(COMMA);
            break;
        case '.':
            add_token(DOT);
            break;
        case '-':
            add_token(MINUS);
            break;
        case '+':
            add_token(PLUS);
            break;
        case ';':
            add_token(SEMICOLON);
            break;
        case '*':
            add_token(STAR);
            break;
        case '!':
            add_token(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            add_token(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            add_token(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            add_token(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if (match('/'))
            {
                while (peek() != '\n' && !is_at_end())
                    advance();
            }
            else
            {
                add_token(SLASH);
            }
            break;

        case '"':
            string();
            break;

        case ' ':
        case '\t':
        case '\r':
            break;
        case '\n':
            line++;
            break;

        default:
            if (is_digit(c))
            {
                number();
            }
            else if (is_alpha(c))
            {
                identifier();
            }
            else
            {
                error(line, "Unexpected character.");
            }
            break;
        }
    }

    bool Scanner::is_alpha_numeric(char c)
    {
        return is_alpha(c) || is_digit(c);
    }

    bool Scanner::is_alpha(char c)
    {
        return c >= 'a' && c <= 'z' ||
               c >= 'A' && c <= 'Z' ||
               c == '_';
    }

    void Scanner::identifier()
    {
        while (is_alpha_numeric(peek()))
        {
            advance();
        }

        std::string text = source.substr(start, current - start);

        auto token_type = keywords.find(text);
        add_token(token_type != keywords.end() ? token_type->second : IDENTIFIER);
    }

    bool Scanner::is_digit(char c)
    {
        return c >= '0' && c <= '9';
    }

    void Scanner::number()
    {
        while (is_digit(peek()))
        {
            advance();
        }

        if (peek() == '.' && is_digit(peek_next()))
        {
            advance();

            while (is_digit(peek()))
            {
                advance();
            }
        }

        add_token(NUMBER, atof(source.substr(start, current - start).c_str()));
    }

    void Scanner::string()
    {
        while (peek() != '"' && !is_at_end())
        {
            if (peek() == '\n')
            {
                line++;
            }
            advance();
        }

        if (is_at_end())
        {
            error(line, "Unterminated string");
            return;
        }

        advance();

        std::string value = source.substr(start + 1, current - start - 2);
        add_token(STRING, value);
    }

    char Scanner::advance()
    {
        return source[current++];
    }

    bool Scanner::match(char expected)
    {
        if (is_at_end())
        {
            return false;
        }
        if (source[current] != expected)
        {
            return false;
        }

        current++;
        return true;
    }

    char Scanner::peek()
    {
        if (is_at_end())
        {
            return '\0';
        }
        return source[current];
    }

    char Scanner::peek_next()
    {
        if (current + 1 >= source.length())
        {
            return '\0';
        }
        return source[current + 1];
    }

    void Scanner::add_token(TokenType type)
    {
        add_token(type, std::nullopt);
    }

    void Scanner::add_token(TokenType type, std::optional<std::any> literal)
    {
        std::string text = source.substr(start, current - start);
        tokens.push_back(Token(type, text, literal, line));
    }

    bool Scanner::is_at_end()
    {
        return current >= source.length();
    }
}