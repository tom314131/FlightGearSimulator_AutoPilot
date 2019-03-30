#include <utility>

#ifndef PROJECT_TOKEN_H
#define PROJECT_TOKEN_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

enum TokenType {
    CMD,        // command
    SP,         // space
    WORD,       // complexed string - may be anything.
    DELIMITER,  // token that splits and doesnt account for
    LCB,        // Left Curly Bracket
    RCB,        // Right Curly Bracket
    MATH,
    NUM,
    BOOL,
    ERR,
    LRB,        // left round bracket
    RRB,        // right round bracket
    STR,        // string
};

class Token {

    TokenType _type;        // type of token.
    string _value;          // the actual value.
    int _priority;          // token priority if matters.
    string _must_be_after;  // chars that one of them must be after.
    string _cant_be_after;  // chars that none of them can be after.

public:

    Token() {}

    Token(TokenType type, const string &value, int priority = 0,
          string must_kriptonite = "",
          string cant_kriptonite = "") {
        this->_type = type;
        this->_value = value;
        this->_priority = priority;
        this->_must_be_after = std::move(must_kriptonite);
        this->_cant_be_after = std::move(cant_kriptonite);
    }

    TokenType get_type() const { return _type; }

    const string &get_value() const { return _value; }

    int getPriority() const {return _priority;}

    // get the char after the token and checks for its validaty with it.
    bool isValidAfterToken(char check) const;
};

#endif