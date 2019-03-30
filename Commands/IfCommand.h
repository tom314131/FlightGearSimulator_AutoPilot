#ifndef PROJECT_IFCOMMAND_H
#define PROJECT_IFCOMMAND_H

#include "ScopeCommand.h"

class IfCommand : public ScopeCommand {

    /***
     * record of line - if its an odd number visit or even number.
     * the scope command execute make the program run until the end of scope,
     * and then execute the first line again.
     * if its the second time, the if command should return stop true no matter
     * the condition.
     * hence, the need to records if should check the condition or not.
     * need to be reset after one full run - so if in a loop - still will be valid
     * each iteration.
     */
    map<int, bool> _linesRecord;

public:

    IfCommand(DataHandler *_dataHandler, VarManager *_varManager,
              ShuntingYard *_expCalculator) : ScopeCommand(_dataHandler,
                                                           _varManager,
                                                           _expCalculator) {}

    bool ShouldStop() override;

    ~IfCommand() override = default;
};

#endif
