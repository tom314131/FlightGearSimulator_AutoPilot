#ifndef AP_FIRSTMILESTONE_EXPRESSION_H
#define AP_FIRSTMILESTONE_EXPRESSION_H

class Expression {

public:
    virtual double Calculate() = 0;

    virtual ~Expression() = 0;
};

inline Expression::~Expression() {}

#endif
