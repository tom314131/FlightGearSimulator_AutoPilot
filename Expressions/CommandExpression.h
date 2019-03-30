#ifndef PROJECT_COMMANDEXPRESSION_H
#define PROJECT_COMMANDEXPRESSION_H

#include "../Commands/Command.h"
#include "Expression.h"

class CommandExpression : public Expression {

    Command *_command;
public:
    CommandExpression(Command *command) {
        this->_command = command;
    }

    double Calculate() override {
        _command->doCommand();
        return 0;
    }

    ~CommandExpression() override {
        delete _command;
    }
};

#endif
