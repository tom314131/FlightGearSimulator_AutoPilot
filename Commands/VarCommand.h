#ifndef PROJECT_VARCOMMAND_H
#define PROJECT_VARCOMMAND_H

#include "Command.h"

#define INIT_VAL 0

class VarCommand : public Command {

public:

    VarCommand(DataHandler *_dataHandler, VarManager *_varManager,
               ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                       _varManager,
                                                       _expCalculator) {}

    void doCommand() override;

    ~VarCommand() override = default;
};

#endif