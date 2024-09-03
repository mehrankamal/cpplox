#include "Expr.hh"

namespace Lox
{

    Binary::Binary(Expr *left, Token op, Expr *right) : left(left), op(op), right(right)
    {
    }
    template <typename R>
    R Binary::visit(ExprVisitor<R> *visitor)
    {
        return visitor->visitBinary(this);
    }
    Binary::~Binary()
    {
    }

    Grouping::Grouping(Expr *expression) : expression(expression)
    {
    }
    template <typename R>
    R Grouping::visit(ExprVisitor<R> *visitor)
    {
        return visitor->visitGrouping(this);
    }
    Grouping::~Grouping()
    {
    }

    Literal::Literal(std::any value) : value(value)
    {
    }
    template <typename R>
    R Literal::visit(ExprVisitor<R> *visitor)
    {
        return visitor->visitLiteral(this);
    }
    Literal::~Literal()
    {
    }

    Unary::Unary(Token op, Expr *right) : op(op), right(right)
    {
    }
    template <typename R>
    R Unary::visit(ExprVisitor<R> *visitor)
    {
        return visitor->visitUnary(this);
    }
    Unary::~Unary()
    {
    }

}
