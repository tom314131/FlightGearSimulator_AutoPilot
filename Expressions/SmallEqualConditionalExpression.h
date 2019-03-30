#ifndef PROJECT_SMALLEQUALCONDITIONALEXPRESSION_H
#define PROJECT_SMALLEQUALCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class SmallEqualConditionalExpression : public BinaryExpression {

public:
    SmallEqualConditionalExpression(Expression *expression1,
                                    Expression *expression2);

    double Calculate() override;
};

#endif