#ifndef PROJECT_NOTEQUALCONDITIONALEXPRESSION_H
#define PROJECT_NOTEQUALCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class NotEqualConditionalExpression : public BinaryExpression {

public:
    NotEqualConditionalExpression(Expression *expression1,
                                  Expression *expression2);

    double Calculate() override;
};

#endif