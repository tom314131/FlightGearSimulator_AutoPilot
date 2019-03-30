#include "DataReaderClient.h"

pthread_t DataReaderClient::StartClient(const string &ip, int port) {

    _params._ip = ip;
    _params._port = port;
    pthread_create(&_params._pthread, nullptr,
                   DataReaderClient::UpdateStatus, this);
    return _params._pthread;
}

void DataReaderClient::ConnectToSimulator() {
    struct sockaddr_in serv_addr{};
    struct hostent *server;

    /* Create a socket point */
    _params._clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (_params._clientSocket < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(_params._ip.c_str());

    if (server == nullptr) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(_params._port);

    /* Now connect to the server */
    if (connect(_params._clientSocket, (struct sockaddr *) &serv_addr,
                sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

void *DataReaderClient::UpdateStatus(void *arg) {
    auto *client = (DataReaderClient *) arg;

    client->ConnectToSimulator();
    /* Now ask for a message from the user, this message
       * will be read by server
    */
    while (!client->ShouldStop()) {
        client->SendToSimulator();
    }
    return nullptr;
}

void DataReaderClient::SendToSimulator() {
    while (!_neededUpdates.empty()) {
        UpdateUnit update = RequestTask(UpdateUnit(), GET_TASK);
        string command =
                "set " + update.path + " " + to_string(update.value) + "\r\n";
        int n = write(_params._clientSocket, command.c_str(), command.size());
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }
}

UpdateUnit DataReaderClient::RequestTask(UpdateUnit update, string request) {
    lock.lock();
    UpdateUnit requested;

    if (request == ADD_TASK) {
        _neededUpdates.push(update);
    } else if (request == GET_TASK) {
        requested = _neededUpdates.front();
        _neededUpdates.pop();
    }
    lock.unlock();
    return requested;
}
