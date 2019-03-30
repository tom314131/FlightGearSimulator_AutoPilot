#ifndef PROJECT_OPENDATASERVERCOMMAND_H
#define PROJECT_OPENDATASERVERCOMMAND_H

#include "Command.h"
#include "../Server_Client/DataReaderServer.h"

#define LOAD_MSG "Please wait until the simulator starts to send information."

class OpenDataServerCommand : public Command {

    DataReaderServer *server;
    pthread_t _serverThread;
public:

    OpenDataServerCommand(DataHandler *_dataHandler, VarManager *_varManager,
                          ShuntingYard *_expCalculator) : Command(_dataHandler,
                                                                  _varManager,
                                                                  _expCalculator) {
        this->server = new DataReaderServer(_varManager);
    }

    void doCommand() override;

    // mark server to stop, wait until its thread is finished, and delete server
    ~OpenDataServerCommand() override {
        server->Stop();
        pthread_join(_serverThread, nullptr);
        delete server;
    }
};


#endif
