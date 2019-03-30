#ifndef PROJECT_BIGCONDITIONALEXPRESSION_H
#define PROJECT_BIGCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class BigConditionalExpression : public BinaryExpression {

public:
    BigConditionalExpression(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif
