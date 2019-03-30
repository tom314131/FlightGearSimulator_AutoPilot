#include "ConnectCommand.h"

/***
 * moves one token from 'connect' to take the ip, then another to take the port.
 * creates and hold a client ref and the thread id of it.
 */
void ConnectCommand::doCommand() {
    _dataHandler->Advance(ONE);
    string ip = _dataHandler->GetCurrentToken().get_value();
    _dataHandler->Advance(ONE);
    string portString = _dataHandler->GetCurrentToken().get_value();
    double port = _expCalculator->GetResults(portString);
    _dataHandler->Advance(ONE);

    _clientThread = client->StartClient(ip, (int) port);
    _varManager->AddClient(client);
}
