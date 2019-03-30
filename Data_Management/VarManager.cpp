#include "VarManager.h"

bool VarManager::IsInSpecialNames(const string &name) {
    bool result = false;
    vector<string>::iterator it;
    for (it = _specialNames.begin(); it != _specialNames.end(); ++it) {
        if ((*it) == name) {
            result = true;
            break;
        }
    }
    return result;
}

void VarManager::Bind(string source, string target) {
    lock.lock();
    if (!IsBindExist(source, target)) {
        _binds[source].push_back(target);
    }
    if (!IsBindExist(target, source)) {
        _binds[target].push_back(source);
    }
    if (target[0] == '\"') {
        _lastBindNeedUpdate = target;
    }
    lock.unlock();
}

bool VarManager::IsBindExist(const string &source, const string &target) {
    bool result = false;
    if (!(_binds.find(source) == _binds.end())) {
        vector<string> source_binds = _binds.at(source);
        vector<string>::iterator it;
        for (it = source_binds.begin(); it != source_binds.end(); it++) {
            if (*it == target) {
                result = true;
                break;
            }
        }
    }
    return result;
}

bool VarManager::hasBind(const string &source) {
    bool result = _binds.find(source) != _binds.end();
    return result;
}

void VarManager::UpdatePath(const string &path, double value) {
    if (_lastBindNeedUpdate == path) {
        _lastBindNeedUpdate.clear();
    }
    if (hasBind(path)) {
        vector<string> source_binds = _binds.at(path);
        vector<string>::iterator it;
        for (it = source_binds.begin(); it != source_binds.end(); it++) {
            if (IsVarExist((*it))) {
                SetVarValue((*it), value);
            }
        }
    }
}

void VarManager::UpdateVar(const string &varName, double value) {
    while (!_lastBindNeedUpdate.empty()) {
        sleep(MILI_SEC); // wait until server sends first update for last bind
    }
    SetVarValue(varName, value);
    UpdateVarBinds(varName);
}

void VarManager::UpdateVarBinds(const string &varName) {
    if (hasBind(varName)) {
        vector<string> source_binds = _binds.at(varName);
        vector<string>::iterator it;
        for (it = source_binds.begin(); it != source_binds.end(); it++) {
            if (IsVarExist((*it))) {
                SetVarValue((*it), _symbolTable.at(varName));
            } else {
                SendSimulatorUpdate((*it), _symbolTable.at(varName));
            }
        }
    }
}

void VarManager::SendSimulatorUpdate(const string &path, double value) {

    if (_client != nullptr) {
        string cleanPath = path.substr(0, path.length() - 1);
        cleanPath = cleanPath.substr(1, cleanPath.length() - 1);
        UpdateUnit unit = {.path = cleanPath, .value = value};
        _client->RequestTask(unit, ADD_TASK);
    }
}

double VarManager::GetValue(const string &varName) {
    double value = _symbolTable[varName];
    return value;
}

void VarManager::AddClient(DataReaderClient *newClient) {
    if (_client == nullptr) {
        _client = newClient;
    }
}

void VarManager::PrintAll() {
    map<string, double>::iterator it;
    for (it = _symbolTable.begin(); it != _symbolTable.end(); it++) {
        cout << (*it).first << ": " << (*it).second << ", ";
    }
    cout << endl << ">>";
}




