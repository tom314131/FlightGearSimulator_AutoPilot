#ifndef AP_FIRSTMILESTONE_EXPRESSIONMANAGER_H
#define AP_FIRSTMILESTONE_EXPRESSIONMANAGER_H

#include <map>
#include <string>

#include "Expression.h"
#include "../Data_Management/VarManager.h"
#include "../Data_Management/DataHandler.h"
#include "../Commands/CommandFactory.h"

#include "CommandExpression.h"

#define UNKNOWN_CMD ", unknown command: "

using namespace std;

class ExpressionManager {

    VarManager _varManager;
    map<string, Expression *> _knownExpressions;

    CommandFactory _factory;

    DataHandler *_dataHandler;

    /**
     * return an expression with existing key.
     * if the expression is not yet created - create it and return it.
     */
    Expression *GetExpression(const string &exp);

    // load known expressions.
    void LoadKnownExpressions();

public:

    ExpressionManager(DataHandler *dataHandler) : _factory(dataHandler) {
        this->_dataHandler = dataHandler;
        this->_factory.SetVarManager(&(this->_varManager));
        LoadKnownExpressions();
    }

    /***
     * checks if current token or next token is a known expression, if so -
     * return it.
     */
    Expression *GetNextExpression();

    // empty the expression map
    void EmptyExpressionMap();

    virtual ~ExpressionManager();
};


#endif
