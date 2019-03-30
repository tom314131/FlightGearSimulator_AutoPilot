#ifndef PROJECT_ENTERCCOMMAND_H
#define PROJECT_ENTERCCOMMAND_H

#include "Command.h"

#define ENTER_MSG "press enter to continue."

class EntercCommand : public Command {

public:
    EntercCommand(DataHandler * d) : Command(d, nullptr, nullptr) {}

    void doCommand() override {
        cout << ENTER_MSG;
        cin.get();
        _dataHandler->Advance(ONE);
    }

    ~EntercCommand() override = default;
};

#endif
