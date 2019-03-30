#ifndef PROJECT_SHUNTINGYARD_H
#define PROJECT_SHUNTINGYARD_H

#include <string>
#include <map>
#include "../Expressions/Expression.h"
#include <regex>
#include "../Data_Management/VarManager.h"
#include "../Data_Management/Tokenizer.h"
#include "../Data_Management/Token.h"
#include <queue>
#include "../Expressions/Div.h"
#include "../Expressions/Mult.h"
#include "../Expressions/Plus.h"
#include "../Expressions/Minus.h"
#include "../Expressions/Number.h"
#include "../Expressions/AndConditionalExpression.h"
#include "../Expressions/OrConditionalExpression.h"
#include "../Expressions/EqualConditionalExpression.h"
#include "../Expressions/NotEqualConditionalExpression.h"
#include "../Expressions/SmallConditionalExpression.h"
#include "../Expressions/SmallEqualConditionalExpression.h"
#include "../Expressions/BigConditionalExpression.h"
#include "../Expressions/BigEqualConditionalExpression.h"

using namespace std;

class ShuntingYard {
    VarManager *varManager;
    Tokenizer tokenizer;

    queue<Token> ShuntingYardAlgorithm(vector<Token> splitPhrase);

    Expression *CalculateQueue(queue<Token> queuE);

    Expression *getFitExp(const string &operation,
                          stack<Expression *> &stackExp);

public:

    ShuntingYard(VarManager *varManager) {
        this->varManager = varManager;
        this->tokenizer.SetShuntingYard();
    }

    double GetResults(string phrase) {
        Expression *e = GetExpression(phrase);
        double result = e->Calculate();
        delete e;
        return result;
    }

    Expression *GetExpression(string phrase) {
        vector<Token> splitPhrase = this->tokenizer.Lex(phrase);
        queue<Token> orderedTokens = ShuntingYardAlgorithm(splitPhrase);
        return CalculateQueue(orderedTokens);
    }
};

#endif
