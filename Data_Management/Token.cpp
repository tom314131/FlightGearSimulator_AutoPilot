#include "Token.h"


bool Token::isValidAfterToken(char check) const {
    bool result = true;

    if (!_must_be_after.empty()) {
        result = false;
        for (char c : _must_be_after) {
            if (check == c) {
                result = true;
                break;
            }
        }
    } else if (!_cant_be_after.empty()) {
        result = true;
        for (char c: _cant_be_after) {
            if (check == c) {
                result = false;
                break;
            }
        }
    }

    return result;
}
