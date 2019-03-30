#include "DataReaderServer.h"

using namespace std;

pthread_t DataReaderServer::StartServer(int port, int hertz) {
    _params._port = port;
    _params._hertz = hertz;

    CreateServerSocket();

    pthread_t trid;
    pthread_create(&trid, nullptr, DataReaderServer::StartListeningForData,
                   this);
    while (!_receivedFirstData) {
        sleep(MILI_SEC);
    }
    return trid;
}

void *DataReaderServer::StartListeningForData(void *arg) {
    auto *server = (DataReaderServer *) arg;
    int numOfReceivedBytes;
    char buffer[256];
    string current_string;
    string leftovers;

    /* If connection is established then start communicating */
    while (!server->stop) {

        bzero(buffer, 256);
        numOfReceivedBytes = (int) read(server->_params._clientSocket, buffer,
                                        255);
        if (numOfReceivedBytes < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        if (AddToCurrent(buffer, current_string, leftovers)) {
            vector<double> convertedInfo = StringSeparatorByComma(
                    current_string);
            server->SendUpdate(convertedInfo);
            current_string.clear();
            server->_receivedFirstData = true;
        }
        sleep(server->_params._hertz / MILI_SEC);
    }

    return nullptr;
}

void DataReaderServer::CreateServerSocket() {
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    _params._serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (_params._serverSocket < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(_params._port);

    /* Now bind the host address using bind() call.*/
    if (bind(_params._serverSocket, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(_params._serverSocket, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    _params._clientSocket = accept(_params._serverSocket,
                                   (struct sockaddr *) &cli_addr,
                                   (socklen_t *) &clilen);

    if (_params._clientSocket < 0) {
        perror("ERROR on accept");
        exit(1);
    }
}

void DataReaderServer::SendUpdate(vector<double> newData) {
    vector<double>::iterator it;
    int index = 0;
    for (it = newData.begin(); it != newData.end(); ++it) {
        if (_varManager->hasBind(_paths[index])) {
            _varManager->UpdatePath(_paths[index], (*it));
        }
        index++;
    }
}

void DataReaderServer::LoadPaths() {
    ifstream file(PATH_FILE);
    int index = 0;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            _paths[index] = line;
            index++;
        }
        file.close();
    }
}


