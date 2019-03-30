#ifndef PROJECT_NUMBER_H
#define PROJECT_NUMBER_H

#include "Expression.h"

class Number : public Expression {
    double num;
public:
    explicit Number(double number);

    double Calculate() override;

    ~Number() override = default;
};

#endif