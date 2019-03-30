#include "SleepCommand.h"

void SleepCommand::doCommand() {
    _dataHandler->Advance(ONE);
    Token sleepTime = _dataHandler->GetCurrentToken();
    this_thread::sleep_for(chrono::milliseconds((unsigned int) stoi
            (sleepTime.get_value())));
    _dataHandler->Advance(ONE);
}

