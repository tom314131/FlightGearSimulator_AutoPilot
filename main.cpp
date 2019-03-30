#include <iostream>
#include <string>
#include <vector>

#include "Expressions/ExpressionManager.h"
#include "Expressions/Expression.h"
#include "Data_Management/DataHandler.h"

#include "Data_Management/Lexer.h"


using namespace std;

void Parser(DataHandler *dataHandler, ExpressionManager *expressionManager);

int main(int args, char **argv) {

    DataHandler dataHandler;
    ExpressionManager expressionManager(&dataHandler);
    string target = args == TWO ? argv[ONE] : NOT_FILE;
    Lexer l = Lexer(&dataHandler, target);

    while (!dataHandler.IsShuttingDown()) {
        // loads dataHandler with new splitted vector of strings
        // either from file or from command line
        l.Interpret();
        Parser(&dataHandler, &expressionManager);
    }
};


void Parser(DataHandler *dataHandler, ExpressionManager *expressionManager) {

    if (dataHandler->GetState() != READ && !dataHandler->ShouldSkipLine()) {
        while (!dataHandler->IsShuttingDown() && dataHandler->hasMoreTokens()) {
            Expression *e = expressionManager->GetNextExpression();
            /**
             * expression might be invalid, dont break the code,
             * just ignore and a message would be printed
             */
            if (e != nullptr) {
                e->Calculate();
            }
        }
    }
}

