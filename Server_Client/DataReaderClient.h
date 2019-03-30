#ifndef PROJECT_DATAREADERCLIENT_H
#define PROJECT_DATAREADERCLIENT_H

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <mutex>

#include <string.h>
#include <string>
#include <queue>
#include <iostream>

#define ADD_TASK "add"
#define GET_TASK "get"

using namespace std;

struct UpdateUnit {
    string path;
    double value;
};

class DataReaderClient {

    bool _stop;
    queue<UpdateUnit> _neededUpdates;
    mutex lock;

public:
    struct ClientParams {
        string _ip;
        int _port;
        int _clientSocket;
        pthread_t _pthread;
    } _params{};

    DataReaderClient() {
        _stop = false;
    };

    // create client thread and start client on it.
    pthread_t StartClient(const string &ip, int port);

    // create a socket and connect to server
    void ConnectToSimulator();

    // while client doesnt need to be stopped, check for task execution.
    static void *UpdateStatus(void *arg);

    // call for task retrieve and send task.
    void SendToSimulator();

    /***
     * get an update and a task as string.
     * if task is add - insert the update to updates queue.
     * if task is get - then pop front update from queue and return it.
     * in the same function for thread locking.
     */
    UpdateUnit RequestTask(UpdateUnit update, string request);

    // return stop status.
    bool ShouldStop() { return _stop; }

    // set stop to true.
    void Stop() { _stop = true; }

};


#endif