#ifndef PROJECT_EQCOMMAND_H
#define PROJECT_EQCOMMAND_H

#include "Command.h"

#define BIND_INDICATOR "bind"

using namespace std;

class EqCommand : public Command {

public:
    EqCommand(DataHandler *_dataHandler, VarManager *_varManager,
              ShuntingYard *_expCalculator) : Command(_dataHandler, _varManager,
                                                      _expCalculator) {}

    void doCommand() override;

    // handles bind requests.
    void HandleBind(const string &varName);

    // handles set value requests.
    void HandleSet(const string &varName);

    ~EqCommand() override = default;
};

#endif
