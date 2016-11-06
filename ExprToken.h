#ifndef __EXPRTOKEN__
#define __EXPRTOKEN__

#include <iostream>
#include <string>

enum type{num, op, par_left, par_right};

class ExprToken{
public:
	ExprToken(const std::string& s);
	type get_type();
	std::string get_value();
	int get_operator_priority() const;
	int compare_priority(const ExprToken& token);

private:
	type _type;
	std::string _value;
};

#endif