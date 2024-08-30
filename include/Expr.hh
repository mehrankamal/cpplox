#pragma once

#include "Token.hh"

namespace Lox
{

    class Expr
    {
    public:
        virtual ~Expr() = default;
    };

    class Binary : public Expr
    {
    public:
        Binary(Expr *left, Token op, Expr *right);
        ~Binary();

        Expr *left;
        Token op;
        Expr *right;
    };
    class Grouping : public Expr
    {
    public:
        Grouping(Expr *expression);
        ~Grouping();

        Expr *expression;
    };
    class Literal : public Expr
    {
    public:
        Literal(std::any value);
        ~Literal();

        std::any value;
    };
    class Unary : public Expr
    {
    public:
        Unary(Token op, Expr *right);
        ~Unary();

        Token op;
        Expr *right;
    };
}
