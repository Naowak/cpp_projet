#ifndef __UTILS__
#define __UTILS__

#include "ExprToken.h"
#include <iostream>
#include <vector>

bool is_operator(const std::string& s);
bool is_number(const std::string& s);
bool is_parentheses(const std::string& s);


std::string set_space(const std::string& s);
std::vector<ExprToken> split (const std::string& s, char delim);


#endif