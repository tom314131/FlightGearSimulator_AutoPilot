#include "Lexer.h"


vector<Token> *Lexer::Split(const string &line) {
    auto *result = new vector<Token>;

    (*result) = _tokenizer.Lex(line);

    return result;
}

void Lexer::CommandLineLexer() {
    string line;
    cout << CONSOLE_PREFIX;
    getline(cin, line);
    if (!line.empty()) {
        vector<Token> *splitted = Split(line);
        _dataHandler->SetNewLine(splitted);
    } else {
        _dataHandler->TriggerSkipLine();
    }
}

void Lexer::LoadFile() {
    ifstream file(this->_target);
    if (file.is_open()) {
        string newLine;
        while (getline(file, newLine)) {
            this->_lines.push_back(newLine);
        }
        file.close();
    }
}

void Lexer::FileLexer() {
    if (_lines.empty()) {
        LoadFile();
        _lineNumber = 0;
    }

    // there has been an error with the code inside the file.
    if (_dataHandler->ShouldSkipLine()) {
        _target = NOT_FILE;
        CommandLineLexer();
        return;
    }

    if ((int) _lines.size() <= _lineNumber) {
        _target = NOT_FILE;
        CommandLineLexer();
    } else {

        string line = _lines[_lineNumber];
        _lineNumber++;

        if (_lineNumber == 15) {
            cout << "";
        }
        vector<Token> *splitted = Split(line);

        _dataHandler->SetNewLine(splitted);
    }
}

void Lexer::Interpret() {
    if (_dataHandler->GetState() != RUN) {
        if (this->_target == NOT_FILE) {
            CommandLineLexer();
        } else {
            FileLexer();
        }
    }
}
