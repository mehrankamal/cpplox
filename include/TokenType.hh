#pragma once

namespace Lox
{
    enum TokenType
    {
        // Single-character tokens.
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        COMMA,
        DOT,
        MINUS,
        PLUS,
        SEMICOLON,
        SLASH,
        STAR,

        // One or two character tokens.
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,

        // Literals.
        IDENTIFIER,
        STRING,
        NUMBER,

        // Keywords.
        AND,
        CLASS,
        ELSE,
        FALSE,
        FUN,
        FOR,
        IF,
        NIL,
        OR,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        TRUE,
        VAR,
        WHILE,

        END_OF_FILE,
    };

    inline std::ostream &operator<<(std::ostream &os, TokenType type)
    {
        switch (type)
        {
        case LEFT_PAREN:
            return os << "LEFT_PAREN";
        case RIGHT_PAREN:
            return os << "RIGHT_PAREN";
        case LEFT_BRACE:
            return os << "LEFT_BRACE";
        case RIGHT_BRACE:
            return os << "RIGHT_BRACE";
        case COMMA:
            return os << "COMMA";
        case DOT:
            return os << "DOT";
        case MINUS:
            return os << "MINUS";
        case PLUS:
            return os << "PLUS";
        case SEMICOLON:
            return os << "SEMICOLON";
        case SLASH:
            return os << "SLASH";
        case STAR:
            return os << "STAR";
        case BANG:
            return os << "BANG";
        case BANG_EQUAL:
            return os << "BANG_EQUAL";
        case EQUAL:
            return os << "EQUAL";
        case EQUAL_EQUAL:
            return os << "EQUAL_EQUAL";
        case GREATER:
            return os << "GREATER";
        case GREATER_EQUAL:
            return os << "GREATER_EQUAL";
        case LESS:
            return os << "LESS";
        case LESS_EQUAL:
            return os << "LESS_EQUAL";
        case IDENTIFIER:
            return os << "IDENTIFIER";
        case STRING:
            return os << "STRING";
        case NUMBER:
            return os << "NUMBER";
        case AND:
            return os << "AND";
        case CLASS:
            return os << "CLASS";
        case ELSE:
            return os << "ELSE";
        case FALSE:
            return os << "FALSE";
        case FUN:
            return os << "FUN";
        case FOR:
            return os << "FOR";
        case IF:
            return os << "IF";
        case NIL:
            return os << "NIL";
        case OR:
            return os << "OR";
        case PRINT:
            return os << "PRINT";
        case RETURN:
            return os << "RETURN";
        case SUPER:
            return os << "SUPER";
        case THIS:
            return os << "THIS";
        case TRUE:
            return os << "TRUE";
        case VAR:
            return os << "VAR";
        case WHILE:
            return os << "WHILE";
        case END_OF_FILE:
            return os << "END_OF_FILE";
        default:
            return os << "UNKNOWN_TOKEN_TYPE";
        }
    }
};