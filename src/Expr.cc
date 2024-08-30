#include "Expr.hh"

namespace Lox
{

    Binary::Binary(Expr *left, Token op, Expr *right) : left(left), op(op), right(right)
    {
    }

    Binary::~Binary()
    {
    }

    Grouping::Grouping(Expr *expression) : expression(expression)
    {
    }

    Grouping::~Grouping()
    {
    }

    Literal::Literal(std::any value) : value(value)
    {
    }

    Literal::~Literal()
    {
    }

    Unary::Unary(Token op, Expr *right) : op(op), right(right)
    {
    }

    Unary::~Unary()
    {
    }

}
