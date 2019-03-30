#include "VarCommand.h"

void VarCommand::doCommand() {
    this->_dataHandler->Advance(ONE);
    Token newVar = this->_dataHandler->GetCurrentToken();

    if (_varManager->IsLegal(newVar.get_value())) {
        this->_varManager->SetVarValue(newVar.get_value(), INIT_VAL);
        this->_dataHandler->Advance(ONE);
    } else {
        SyntaxErrorHandler(_dataHandler->GetTokenInOffSet(-1));
    }
}
