#ifndef PROJECT_EQUALCONDITIONALEXPRESSION_H
#define PROJECT_EQUALCONDITIONALEXPRESSION_H

#include "BinaryExpression.h"

class EqualConditionalExpression : public BinaryExpression {

public:
    EqualConditionalExpression(Expression *expression1,
                               Expression *expression2);

    double Calculate() override;
};


#endif
