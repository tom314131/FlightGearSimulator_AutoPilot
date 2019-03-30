#ifndef PROJECT_CONNECTCOMMAND_H
#define PROJECT_CONNECTCOMMAND_H

#include "Command.h"
#include "../Server_Client/DataReaderClient.h"

// responsible on closing the client thread and deleting the client.
class ConnectCommand : public Command {

    DataReaderClient *client;
    pthread_t _clientThread;
public:
    ConnectCommand(DataHandler *_dataHandler, VarManager *_varManager,
                   ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                           _varManager,
                                                           _expCalculator) {
        client = new DataReaderClient();
    }

    void doCommand() override;

    ~ConnectCommand() override {
        client->Stop();
        pthread_join(_clientThread, nullptr);
        delete client;
    }
};

#endif