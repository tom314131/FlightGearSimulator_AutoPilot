#ifndef TRY_UTILS_H
#define TRY_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

//
vector<double> StringSeparatorByComma(string input);

bool UpdateCurrentFromLeftOvers(string &current_string, string &leftovers);

bool AddToCurrent(const string &buffer, string &current_string,
                  string &leftovers);


#endif
