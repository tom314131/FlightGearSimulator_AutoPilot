#ifndef PROJECT_BINARYEXPRESSION_H
#define PROJECT_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {

protected:
    Expression *exp1;
    Expression *exp2;

public:
    double Calculate() override = 0;

    ~BinaryExpression() override {
        delete exp1;
        delete exp2;
    };
};

#endif
