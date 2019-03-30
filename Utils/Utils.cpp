#include "Utils.h"

/**
 * receives a string of doubles separated by ','.
 * returns vector of doubles with these values.
 */
vector<double> StringSeparatorByComma(string input) {

    vector<double> result;
    string currentValue;
    int index = 0;

    while (index < input.length()) {
        if (input[index] == ',') {
            if (!currentValue.empty()) {
                result.push_back(stod(currentValue));
                currentValue.clear();
            }
        } else {
            currentValue += input[index];
        }
        index++;
    }

    if (!currentValue.empty()) {
        result.push_back(stod(currentValue));
    }

    return result;
}

/***
 * receives a string and a leftover string.
 * loads leftovers substring into current until reaches the end of leftover
 * or '\n'.
 * updates the leftover sub string the leftovers.
 * if encountered '\n', return true, else false.
 */
bool UpdateCurrentFromLeftOvers(string &current_string, string &leftovers) {
    bool hasNewLine = false;

    if (!leftovers.empty()) {
        int index = 0;
        while (index < leftovers.length()) {
            if (leftovers[index] != '\n') {
                current_string += leftovers[index];
            } else {
                hasNewLine = true;
                break;
            }
            index++;
        }
        if(index == leftovers.length()){
            leftovers.clear();
        } else{
            leftovers = leftovers.substr(index + 1, leftovers.length() - index - 1);
        }
    }

    return hasNewLine;
}

/***
 * receives a buffer, current string and leftovers.
 * load leftovers into current string by its logic above.
 * if still hasn't encountered '\n\, then load buffer substring to current
 * until reaches the end or '\n'.
 * if encountered '\n' and buffer has more chars, loads them to leftover.
 * if encountered '\n' anywhere, returns true, else returns false.
 */
bool AddToCurrent(const string &buffer, string &current_string,
                  string &leftovers) {
    int index = 0;
    bool hasNewLine = UpdateCurrentFromLeftOvers(current_string, leftovers);

    while (index < buffer.length()) {
        if (buffer[index] == '\n') {
            if (hasNewLine) {
                leftovers += buffer[index];
            } else {
                hasNewLine = true;
            }
        } else if (hasNewLine) {
            leftovers += buffer[index];
        } else {
            current_string += buffer[index];
        }
        index++;
    }

    return hasNewLine;
}

