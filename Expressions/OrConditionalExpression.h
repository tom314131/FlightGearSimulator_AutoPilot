#ifndef PROJECT_ORCONDITIONALEXPRESSION_H
#define PROJECT_ORCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class OrConditionalExpression : public BinaryExpression {

public:
    OrConditionalExpression(Expression *expression1, Expression *expression2);

    double Calculate() override;
};

#endif