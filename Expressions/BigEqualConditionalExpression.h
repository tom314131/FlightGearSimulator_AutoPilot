#ifndef PROJECT_BIGEQUALCONDITIONALEXPRESSION_H
#define PROJECT_BIGEQUALCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class BigEqualConditionalExpression : public BinaryExpression {

public:
    BigEqualConditionalExpression(Expression *expression1,
                                  Expression *expression2);

    double Calculate() override;
};

#endif
