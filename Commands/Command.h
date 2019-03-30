#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H


#include "../Data_Management/DataHandler.h"
#include "../Utils/ShuntingYard.h"

#define STNX_ERR "syntax error in command: "

class Command {

protected:
    DataHandler *_dataHandler;
    VarManager *_varManager;
    ShuntingYard *_expCalculator;

public:
    Command(DataHandler *_dataHandler, VarManager *_varManager = nullptr,
            ShuntingYard *_expCalculator = nullptr) :
            _dataHandler(_dataHandler), _varManager(_varManager),
            _expCalculator(_expCalculator) {}

    void SetCalculator(ShuntingYard *calc) {
        this->_expCalculator = calc;
    }

    void SyntaxErrorHandler(const Token &t) {
        _dataHandler->InvalidLineHandle(STNX_ERR + t.get_value());
    }

    //MUST advance handler by parameters used + 1
    virtual void doCommand() = 0;

    virtual ~Command() = 0;
};

inline Command::~Command() {}

#endif
