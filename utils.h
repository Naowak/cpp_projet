#ifndef __UTILS__
#define __UTILS__

#include "ExprToken.h"
#include <iostream>
#include <vector>

using namespace std;

bool is_operator(const string& s);
bool is_number(const string& s);
bool is_parentheses(const string& s);


string set_space(const string& s);
vector<ExprToken> split (const string& s, char delim);


#endif