#ifndef PROJECT_DATAREADERSERVER_H
#define PROJECT_DATAREADERSERVER_H

#include "../Data_Management/VarManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include <string>
#include <fstream>
#include "../Utils/Utils.h"

#define PATH_FILE "paths.txt"

class DataReaderServer {

    map<int, string> _paths;
    VarManager *_varManager;
    bool _receivedFirstData;
    bool stop;

public:
    struct ServerParams {
        int _port;
        int _hertz;
        int _serverSocket;
        int _clientSocket;
    } _params{};

    explicit DataReaderServer(VarManager *varManager) {
        this->_varManager = varManager;
        this->stop = false;
        this->_receivedFirstData = false;
        LoadPaths();
    }

    // read paths from path.txt file into path map.
    void LoadPaths();

    // create server thread and start server on it.
    pthread_t StartServer(int port, int hertz);

    // create server socket
    void CreateServerSocket();

    // while server doesnt need to be stopped, check read and update var manager
    static void *StartListeningForData(void *arg);

    /***
     * receive vector of data, and for data that is bound in var manager,
     * call update on path in var manager.
     */
    void SendUpdate(vector<double> newData);

    // set stop to true.
    void Stop() { stop = true; }
};

#endif