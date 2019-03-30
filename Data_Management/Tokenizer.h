#include <utility>

#ifndef PROJECT_TOKENIZER_H
#define PROJECT_TOKENIZER_H

#include "Token.h"
#include <vector>
#include <list>

#define SPACE ' '

using namespace std;

struct PacketAnalyzer {
    string line;                // the current string to tokenize
    vector<Token> new_tokens;   // the result vector
    string current_value;       // sum of chars from the string
    int index = 0;              // index of char in string.
};

/***
 * this class responsible on dividing a string to vector of tokens.
 * all valid token are set in Set functions before run.
 * can add token behavior at DoTokenSpec function.
 * if merge expression bool is true, the after the split, the object merges all
 * the expressions into tokens of strings and commands,
 * the rules upon merging tokens or seperating them are in
 * MergeExpressionToOneString.
 * separating is done but this logic and sequence of tokens that is marked as
 * split, and these sequence populates in PopulateSplitSequences.
 */
class Tokenizer {

    list<Token> valid_tokens;   // list of valid tokens.
    bool _mergeExpressions;     // if tokens needs to be merged after split
    // this option is to merge expressions into one string like:
    // "((10+variable)/5)*100"

    // get a token from given string
    Token GetToken(const string &value);

    // checks if given string is a number
    bool IsNumber(const string &value);

    /***
     * checks if current state of pa - string starts from pa index in current
     * string, is equal and valid for given token.
     */
    bool IsToken(const PacketAnalyzer &pa, const Token &t);

    /***
     * do the given token specification on the current state of pa.
     */
    void DoTokenSpecification(PacketAnalyzer &pa, const Token &t);

    /***
     * analyze given packet.
     */
    void AnalyzePacket(PacketAnalyzer &pa);

public:

    Tokenizer() { _mergeExpressions = false; }

    /***
     * creates a new packet analyzer with given string, analyze it and
     * return the result.
     */
    vector<Token> Lex(string str);

    /***
     * add vector of tokens, that if seen near each other in the given order,
     * then the merging will not merge them into one token.
     */
    void PopulateSplitSequences(list<vector<Token>> &skipSequences);

    /***
     * merge the result vector of the given pa into new vector of tokens,
     * by merging logic using split sequences.
     */
    vector<Token> MergeExpressionToStrings(PacketAnalyzer &pa);

    // given a string - if not empty, push it as a token into given vector.
    void PushSumAsToken(vector<Token> &afterMerge, string &tokenSum);

    // add known expressions of commands and merging flag.
    void SetCommandTokenizer();

    // add known expressions of shunting yard.
    void SetShuntingYard();

    void ToLowerCase(Token &t);
};

#endif