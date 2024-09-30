#pragma once

#include "Token.hh"

namespace Lox
{

    template <typename R>
    class ExprVisitor;

    class Expr
    {
    public:
        virtual std::any visit(ExprVisitor<std::any> &visitor) = 0;
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
        virtual R visit_binary(Binary *expr) = 0;
        virtual R visit_grouping(Grouping *expr) = 0;
        virtual R visit_literal(Literal *expr) = 0;
        virtual R visit_unary(Unary *expr) = 0;
    };
}
