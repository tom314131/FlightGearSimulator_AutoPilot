#include "ExpressionManager.h"

Expression *ExpressionManager::GetExpression(const string &exp) {
    Expression *target = _knownExpressions[exp];

    if (target == nullptr) {
        target = new CommandExpression(_factory.GetCommand(exp));
        _knownExpressions[exp] = target;
    }

    return target;
}

void ExpressionManager::LoadKnownExpressions() {
    _knownExpressions["var"] = nullptr;
    _knownExpressions["="] = nullptr;
    _knownExpressions["sleep"] = nullptr;
    _knownExpressions["print"] = nullptr;
    _knownExpressions["openDataServer"] = nullptr;
    _knownExpressions["connect"] = nullptr;
    _knownExpressions["if"] = nullptr;
    _knownExpressions["while"] = nullptr;
    _knownExpressions["exit"] = nullptr;
    _knownExpressions["enterc"] = nullptr;
    _knownExpressions["help"] = nullptr;
}

Expression *ExpressionManager::GetNextExpression() {
    string exp = _dataHandler->GetCurrentToken().get_value();

    if (!(_knownExpressions.find(exp) == _knownExpressions.end())) {
        // is an expression in map
        return GetExpression(exp);
    } else { // is not an expression, may be var - check next

        _dataHandler->Advance(NEXT);
        if (_dataHandler->hasMoreTokens()) {
            exp = _dataHandler->GetCurrentToken().get_value();

            if (!(_knownExpressions.find(exp) == _knownExpressions.end())) {
                return GetExpression(exp);
            }

        }
    }
    _dataHandler->InvalidLineHandle(UNKNOWN_CMD + exp);
    return nullptr;
}

void ExpressionManager::EmptyExpressionMap() {
    map<string, Expression *>::iterator it;
    for (it = _knownExpressions.begin(); it != _knownExpressions.end(); it++) {
        delete (*it).second; // has no effect if ptr is null
    }
}


ExpressionManager::~ExpressionManager() {
    EmptyExpressionMap();
}
