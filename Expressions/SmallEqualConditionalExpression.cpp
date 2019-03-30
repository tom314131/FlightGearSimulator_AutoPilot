#include "SmallEqualConditionalExpression.h"

SmallEqualConditionalExpression::SmallEqualConditionalExpression
        (Expression *expression1, Expression *expression2) {
    this->exp1 = expression1;
    this->exp2 = expression2;
}

double SmallEqualConditionalExpression::Calculate() {
    return this->exp1->Calculate() <= this->exp2->Calculate();
}