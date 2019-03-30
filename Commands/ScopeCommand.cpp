#include "ScopeCommand.h"

/***
 * scope is ready by data handler, check if should stop - skip all scope,
 * or start running it by going to the next line.
 * else, tell data handler to build the scope.
 */
void ScopeCommand::doCommand() {
    SetScope();

    // if scope ready then run the command
    if (_dataHandler->IsScopeReady(_start_line)) {
        if (ShouldStop()) {
            _dataHandler->SkipCurrentScope();
        } else {
            _dataHandler->GoToNextLine();
        }
    } else {
        _dataHandler->BuildScope();
    }
}

// set current scope params, and set the right condition.
void ScopeCommand::SetScope() {
    this->_start_line = _dataHandler->GetCurrentLineIndex();
    if (this->_condition != nullptr) {
        delete this->_condition;
    }
    this->_condition = _expCalculator->GetExpression(
            _dataHandler->GetTokenInOffSet(ONE).get_value());
}

ScopeCommand::~ScopeCommand() {
    delete _condition;
}
