#include "AndConditionalExpression.h"

AndConditionalExpression::AndConditionalExpression
        (Expression *expression1, Expression *expression2) {
    this->exp1 = expression1;
    this->exp2 = expression2;
}

double AndConditionalExpression::Calculate() {
    return this->exp1->Calculate() != 0 && this->exp2->Calculate() != 0;
}