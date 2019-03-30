#ifndef PROJECT_SLEEPCOMMAND_H
#define PROJECT_SLEEPCOMMAND_H

#include "Command.h"
#include <chrono>
#include <thread>
#include <stdexcept>

using namespace std;

class SleepCommand : public Command {

public:
    SleepCommand(DataHandler *_dataHandler, VarManager *_varManager,
                 ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                         _varManager,
                                                         _expCalculator) {}

    void doCommand() override;

    ~SleepCommand() override = default;
};

#endif
