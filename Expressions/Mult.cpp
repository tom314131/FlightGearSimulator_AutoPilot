#include "Mult.h"

Mult::Mult(Expression *expression1, Expression *expression2) {
    this->exp1 = expression1;
    this->exp2 = expression2;
}

double Mult::Calculate() {
    double d1 = this->exp1->Calculate();
    double d2 = this->exp2->Calculate();
    return d1 * d2;
}