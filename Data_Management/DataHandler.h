#ifndef AP_FIRSTMILESTONE_DATAHANDLER_H
#define AP_FIRSTMILESTONE_DATAHANDLER_H

#include <vector>
#include <stack>
#include "Tokenizer.h"

#define BRACKETS_ERR "Brackets error."
#define NEXT 1
#define START_BRACkETS_NUM 0
#define RESET_TOKEN_INDEX 0
#define RESET_LINE_INDEX -1
#define MINUS_ONE -1
#define INVALID_LINE_ERR "Error occurred in line: " << _currentLineIndex
#define ONE 1
#define TWO 2
#define INDEX_OFFSET_ERR Token(ERR,"offset out of range");

using namespace std;

struct BracketPair {
    int _openLine;
    int _closeLine;
};

enum recv_state {
    READ,       // only read
    EXECUTE,    // read and execute
    RUN,        // only execute
    HALT,       // shutting down
};

/**
 * this class controls and holds the lines as vector of token for each line.
 * responsible to mark the current line and current token in line.
 * also have the responsibility to read scopes, and when running on a scope,
 * which is only when it has a valid pairs, keep track and serve the next data.
 * controls the flow with states: execute - interpreter - mark current(last)
 * line for the rest to execute and run on it.
 * read - only reading lines - when building scopes for if and while.
 * run - after finishing building the main scope - lexer won't be adding new
 * lines until the scope is finished, parser will execute the current token,
 * so keep track and redirect '}' to is opener.
 */
class DataHandler {
    vector<vector<Token> *> _all_lines;
    int _currentLineIndex;
    int _currentTokenIndex;
    // marks that the current line is not for execution, and if trigger,
    // will set back to default when new line is read.
    bool _skipLine;

    recv_state _state;

    int runUntilLine;   // main scope last line - '}'
    int _openBrackets;  // number of currently unclosed brackets - in READ state
    vector<BracketPair *> _brackets;  // all brackets pairs - keep track
    stack<BracketPair *> _brackets_queue; // for building main scopes.

    // get open bracket line by given close bracket line.
    int GetStartOfScope(int closeLine);

    // checks if bracket pair that stats in given line exits.
    bool IsBracketPairExists(int startLine);

    // add open bracket of given line.
    void AddOpenBracket(int startLine);

    // add close bracket of given line.
    void AddCloseBracket(int closeLine);

    // checks if given token is in current line.
    bool hasTokenTypeInCurrentLine(const TokenType &type);

    // switch state to execute, reset open brackets num and empty brackets queue
    void ResetScopeControl();

    // empty all brackets fron brackets queue.
    void EmptyBracketsQueue();

    // delete all brackets pair in _brackets.
    void EmptyBrackets();

    // handle execute state.
    void HandleEXECUTEState();

    // upon invalid line - resets scope control and continue with EXECUTE mode.
    void HandleREADState();

    // handle run state
    void HandleRUNState();

    // handles states
    void HandleStates();

public:

    DataHandler() {
        this->_currentLineIndex = RESET_LINE_INDEX;
        this->_state = EXECUTE;
        this->_openBrackets = 0;
        this->_skipLine = false;
    }

    // Getters
    // get current token.
    Token GetCurrentToken();

    // get token in off set in current line.
    Token GetTokenInOffSet(int offset);

    // get current state.
    recv_state GetState() {
        return _state;
    }

    // get current line index.
    int GetCurrentLineIndex() {
        return _currentLineIndex;
    }

    // get size of current line.
    int GetLineSize() {
        return (int) _all_lines[_currentLineIndex]->size();
    }

    // its name.
    int GetEndOfScope(int startLine);

    // functionality for data control
    // adding new line, resetting indexing and calls handle states after.
    void SetNewLine(vector<Token> *newLine);

    // its name.
    void Advance(int steps);

    // its name.
    void SetState(recv_state _state) {
        this->_state = _state;
    }

    // its name.
    void SetTokenIndexToEndOfLine() {
        _currentTokenIndex = (int) _all_lines[_currentLineIndex]->size();
    }

    // marks skipLine as true. - will not execute until new line is read.
    void TriggerSkipLine();

    // switch state to read, and moves the token index to eol.
    void BuildScope();

    // switch state to run, marks the end line of this run by scope.
    void StartRun();

    // switch state to run and moves to last added line.
    void StopRun();

    // if there is another line, advance line, reset token index and handle states.
    void GoToNextLine();

    // print error message with line number and optionally the extra string.
    void InvalidLineHandle(string extra);

    // skip the scope that starts from this line.
    void SkipCurrentScope();

    // Information functions
    // check if current line with current token has more tokens.
    bool hasMoreTokens();

    // returns if data marked the line as not to execute or run.
    bool ShouldSkipLine();

    // returns if the scope that starts in given line number is ready to run.
    bool IsScopeReady(int scopeLine) { return _openBrackets == 0; }

    // return is the state of data handler is HALT.
    bool IsShuttingDown();

    // deletes all data in lines.
    void EraseAllLines();

    // deletes all data in object.
    void EraseAll();
};

#endif
