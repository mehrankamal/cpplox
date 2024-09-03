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
        template <typename R>
        R visit(ExprVisitor<R> *visitor);
        ~Binary();

        Expr *left;
        Token op;
        Expr *right;
    };

    class Grouping : public Expr
    {
    public:
        Grouping(Expr *expression);
        template <typename R>
        R visit(ExprVisitor<R> *visitor);
        ~Grouping();

        Expr *expression;
    };

    class Literal : public Expr
    {
    public:
        Literal(std::any value);
        template <typename R>
        R visit(ExprVisitor<R> *visitor);
        ~Literal();

        std::any value;
    };

    class Unary : public Expr
    {
    public:
        Unary(Token op, Expr *right);
        template <typename R>
        R visit(ExprVisitor<R> *visitor);
        ~Unary();

        Token op;
        Expr *right;
    };

    template <typename R>
    class ExprVisitor
    {
    public:
        virtual R visitBinary(Binary *expr) = 0;
        virtual R visitGrouping(Grouping *expr) = 0;
        virtual R visitLiteral(Literal *expr) = 0;
        virtual R visitUnary(Unary *expr) = 0;
    };
}
