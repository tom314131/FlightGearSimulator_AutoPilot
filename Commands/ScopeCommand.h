#ifndef PROJECT_SCOPECOMMAND_H
#define PROJECT_SCOPECOMMAND_H

#include "Command.h"
#include <list>

class ScopeCommand : public Command {

    int _start_line;
protected:
    Expression *_condition;

public:
    ScopeCommand(DataHandler *_dataHandler, VarManager *_varManager,
                 ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                         _varManager,
                                                         _expCalculator) {
        this->_condition = nullptr;
    }

    void doCommand() override;

    /**
    * set scope parameters
    */
    void SetScope();

    virtual bool ShouldStop() = 0;

    ~ScopeCommand() override;
};

#endif