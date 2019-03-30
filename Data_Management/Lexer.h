#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include "../Expressions/ExpressionManager.h"
#include "DataHandler.h"
#include <fstream>
#include "Tokenizer.h"

#define NOT_FILE "not a file."
#define CONSOLE_PREFIX ">> "

using namespace std;

class Lexer {

    DataHandler *_dataHandler;
    Tokenizer _tokenizer;

    vector<string> _lines;
    int _lineNumber;
    string _target;


    // receives a string and split it to vector of token using the tokenizer.
    vector<Token> *Split(const string &line);

    // prompt PREFIX and wait for next command.
    void CommandLineLexer();

    // load a File into vector of strings.
    void LoadFile();

    /**
     * if target is a file, then load once and read the relative line.
     * if time loads all the file, each call read one new line.
     * if done running on lines, switch to command line lexer.
     */
    void FileLexer();

public:

    Lexer(DataHandler *dataHandler, const string &target) {
        this->_dataHandler = dataHandler;
        this->_target = target;
        this->_tokenizer.SetCommandTokenizer();
    }


    // handles lexing by target - file or command, if need to read new line.
    void Interpret();
};


#endif
