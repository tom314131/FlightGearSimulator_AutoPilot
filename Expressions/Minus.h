#ifndef PROJECT_MINUS_H
#define PROJECT_MINUS_H

#include "BinaryExpression.h"

class Minus : public BinaryExpression {

public:
    Minus(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif
