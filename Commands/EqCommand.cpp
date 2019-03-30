#include "EqCommand.h"

void EqCommand::doCommand() {
    _dataHandler->Advance(MINUS_ONE);
    string varName = _dataHandler->GetCurrentToken().get_value();

    if (!_varManager->IsVarExist(varName)) {
        SyntaxErrorHandler(_dataHandler->GetTokenInOffSet(ONE));
    }

    _dataHandler->Advance(TWO);
    string value = _dataHandler->GetCurrentToken().get_value();

    if (value == BIND_INDICATOR) {
        HandleBind(varName);
    } else {
        HandleSet(varName);
    }

    this->_dataHandler->Advance(ONE);
}

void EqCommand::HandleBind(const string &varName) {
    _dataHandler->Advance(ONE);
    string value = this->_dataHandler->GetCurrentToken().get_value();

    if (value[0] == '\"' || _varManager->IsVarExist(value)) {  // path or var
        _varManager->Bind(varName, value);
    } else {    // not a bind type - get '=' token.
        SyntaxErrorHandler(_dataHandler->GetTokenInOffSet(-2));
    }
}

void EqCommand::HandleSet(const string &varName) {
    string expression = _dataHandler->GetCurrentToken().get_value();
    double newValue = _expCalculator->GetResults(expression);
    _varManager->UpdateVar(varName, newValue);
}

