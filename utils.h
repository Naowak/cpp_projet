#ifndef __UTILS__
#define __UTILS__

#include <iostream>
#include <vector>
#include <string>

class Map{
public:
	double get_value(std::string name);
	double set_value(std::string name, double value);
private:
	std::vector<double> _values;
	std::vector<std::string> _names;
};

#include "ExprToken.h"

bool is_operator(const std::string& s);
bool is_number(const std::string& s);
bool is_parentheses(const std::string& s);
bool is_id(const std::string& s);

void error();

ExprToken* create_expr_token(const std::string& s);

std::string set_space(const std::string& s);
std::vector<ExprToken*> split (const std::string& s, char delim);
std::vector<std::string> split_in_string (const std::string& s, char delim);


#endif