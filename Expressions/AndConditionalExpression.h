#ifndef PROJECT_ANDCONDITIONALEXPRESSION_H
#define PROJECT_ANDCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class AndConditionalExpression : public BinaryExpression {

public:
    AndConditionalExpression(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif
