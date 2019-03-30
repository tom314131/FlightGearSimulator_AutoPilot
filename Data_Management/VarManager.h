#include <utility>

#ifndef PROJECT_VARMANAGER_H
#define PROJECT_VARMANAGER_H

#include <map>
#include <string>
#include <vector>
#include "../Expressions/Expression.h"
#include <mutex>
#include <pthread.h>
#include "../Server_Client/DataReaderClient.h"

#define MILI_SEC 1/1000

using namespace std;

class VarManager {

    map<string, double> _symbolTable;
    map<string, vector<string> > _binds;
    string _lastBindNeedUpdate;
    vector<string> _specialNames;

    DataReaderClient *_client;
    mutex lock;

public:
    VarManager() {
        _client = nullptr;
        _lastBindNeedUpdate.clear();
    };

    // Setters
    // set var value and only its value.
    void SetVarValue(const string &var, double value) {
        lock.lock();
        this->_symbolTable[var] = value;
        lock.unlock();
    }

    // add bind between two strings - each may be var or path
    void Bind(string source, string target);

    // update all binds of given path
    void UpdatePath(const string &path, double value);

    // updates a given var
    void UpdateVar(const string &varName, double value);

    // update all the binds of a given var
    void UpdateVarBinds(const string &varName);

    // add a task to update given path with given value to client.
    void SendSimulatorUpdate(const string &path, double value);

    // add client pointer
    void AddClient(DataReaderClient *newClient);

    // Getters
    double GetValue(const string &varName);

    // Infromation
    bool IsInSpecialNames(const string &name);

    bool IsLegal(const string &varName) {
        return !IsVarExist(varName) && !IsInSpecialNames(varName) &&
               !IsFirstCharNum(varName);
    }

    bool IsFirstCharNum(const string &varName) {
        return (47 < varName[0] && varName[0] < 58);
    }

    bool IsVarExist(const string &var) {
        return !(this->_symbolTable.find(var) == this->_symbolTable.end());
    }

    // chech for specific bind
    bool IsBindExist(const string &source, const string &target);

    // given string - may be var name or path
    bool hasBind(const string &source);

    void PrintAll();
};

#endif