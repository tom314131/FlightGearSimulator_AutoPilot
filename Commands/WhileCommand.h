#ifndef PROJECT_WHILE_H
#define PROJECT_WHILE_H

#include "ScopeCommand.h"


class WhileCommand : public ScopeCommand {

public:
    WhileCommand(DataHandler *_dataHandler, VarManager *_varManager,
                 ShuntingYard *_expCalculator) : ScopeCommand(_dataHandler,
                                                              _varManager,
                                                              _expCalculator) {}

    bool ShouldStop() override {
        return _condition->Calculate() == 0;
    }

    ~WhileCommand() override = default;
};

#endif
