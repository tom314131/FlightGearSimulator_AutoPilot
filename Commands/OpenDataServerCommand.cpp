#include "OpenDataServerCommand.h"

void OpenDataServerCommand::doCommand() {
    cout << LOAD_MSG << endl;
    _dataHandler->Advance(ONE);
    string portString = _dataHandler->GetCurrentToken().get_value();
    double port = _expCalculator->GetResults(portString);

    _dataHandler->Advance(ONE);
    string hertzString = _dataHandler->GetCurrentToken().get_value();
    double hertz = _expCalculator->GetResults(hertzString);

    _dataHandler->Advance(ONE);

    _serverThread = this->server->StartServer((int) port, (int) hertz);
}
