#ifndef PROJECT_SMALLCONDITIONALEXPRESSION_H
#define PROJECT_SMALLCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class SmallConditionalExpression : public BinaryExpression {

public:
    SmallConditionalExpression(Expression *expression1,
                               Expression *expression2);

    double Calculate() override;
};

#endif