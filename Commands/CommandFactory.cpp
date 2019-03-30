#include "CommandFactory.h"

Command *CommandFactory::GetCommand(const string &name) {

    Command *target;
    if (name == "var" || name == "Var") {
        target = new VarCommand(this->_dataHandler, this->_varManager,
                                this->_expressionCalculator);
    } else if (name == "=") {
        target = new EqCommand(this->_dataHandler, this->_varManager,
                               this->_expressionCalculator);
    } else if (name == "sleep" || name == "Sleep") {
        target = new SleepCommand(this->_dataHandler, this->_varManager,
                                  this->_expressionCalculator);
    } else if (name == "print" || name == "Print") {
        target = new PrintCommand(this->_dataHandler, this->_varManager,
                                  this->_expressionCalculator);
    } else if (name == "openDataServer" || name == "OpenDataServer") {
        target = new OpenDataServerCommand(this->_dataHandler,
                                           this->_varManager,
                                           this->_expressionCalculator);
    } else if (name == "connect" || name == "Connect") {
        target = new ConnectCommand(this->_dataHandler, this->_varManager,
                                    this->_expressionCalculator);
    } else if (name == "while") {
        target = new WhileCommand(this->_dataHandler, this->_varManager,
                                  this->_expressionCalculator);
    } else if (name == "if") {
        target = new IfCommand(this->_dataHandler, this->_varManager,
                               this->_expressionCalculator);
    } else if (name == "exit") {
        target = new ExitCommand(this->_dataHandler, this->_varManager,
                                 this->_expressionCalculator);
    } else if (name == "enterc") {
        target = new EntercCommand(this->_dataHandler);
    } else if (name == "help") {
        target = new HelpCommand(this->_dataHandler, this->_varManager);
    }
    return target;
}

CommandFactory::~CommandFactory() {
    delete _expressionCalculator;
}

