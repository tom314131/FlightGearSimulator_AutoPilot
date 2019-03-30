#include "PrintCommand.h"

void PrintCommand::doCommand() {
    _dataHandler->Advance(ONE);
    Token toPrint = _dataHandler->GetCurrentToken();
    if (toPrint.get_value()[0] == '\"') {
        string stringToShow = toPrint.get_value().substr(1,
                                                         toPrint.get_value().length());
        stringToShow = stringToShow.substr(0, stringToShow.length() - 1);
        cout << stringToShow << endl;
    } else {
        cout << _expCalculator->GetResults(toPrint.get_value()) << endl;
    }
    _dataHandler->Advance(ONE);
}

