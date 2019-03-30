#ifndef PROJECT_PRINTCOMMAND_H
#define PROJECT_PRINTCOMMAND_H

#include "Command.h"
#include <iostream>

using namespace std;

class PrintCommand : public Command {

public:
    PrintCommand(DataHandler *_dataHandler, VarManager *_varManager,
                 ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                         _varManager,
                                                         _expCalculator) {}

    void doCommand() override;

    ~PrintCommand() override = default;
};

#endif