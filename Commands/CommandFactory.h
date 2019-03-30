#ifndef PROJECT_COMMANDFACTORY_H
#define PROJECT_COMMANDFACTORY_H

#include <string>
#include "../Utils/ShuntingYard.h"

#include "EntercCommand.h"
#include "VarCommand.h"
#include "EqCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "OpenDataServerCommand.h"
#include "ConnectCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "ExitCommand.h"
#include "HelpCommand.h"

using namespace std;

/***
 * this class responsibles to create given command with it's needed params.
 * in this program this class sits inside expression manager and is given
 * its varmanager. it creates its own expression calculator and gives it to
 * the different classes.
 */
class CommandFactory {

    DataHandler *_dataHandler;
    VarManager *_varManager;
    ShuntingYard *_expressionCalculator;

public:

    explicit CommandFactory(DataHandler *dataHandler) {
        this->_dataHandler = dataHandler;
        this->_varManager = nullptr;
        this->_expressionCalculator = nullptr;
    }

    Command *GetCommand(const string &name);

    void SetVarManager(VarManager *varManager) {
        this->_varManager = varManager;
        this->_expressionCalculator = new ShuntingYard(varManager);
    }

    virtual ~CommandFactory();
};

#endif
