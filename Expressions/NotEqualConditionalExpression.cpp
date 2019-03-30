#include "NotEqualConditionalExpression.h"

NotEqualConditionalExpression::NotEqualConditionalExpression
        (Expression *expression1, Expression *expression2) {
    this->exp1 = expression1;
    this->exp2 = expression2;
}

double NotEqualConditionalExpression::Calculate() {
    return this->exp1->Calculate() != this->exp2->Calculate();
}