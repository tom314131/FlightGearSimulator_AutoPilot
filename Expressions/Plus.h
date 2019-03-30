#ifndef PROJECT_PLUS_H
#define PROJECT_PLUS_H

#include "BinaryExpression.h"

class Plus : public BinaryExpression {

public:
    Plus(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif