#ifndef __EXPRTOKEN__
#define __EXPRTOKEN__

#include <iostream>
#include <string>

using namespace std;

class ExprToken{
public:
	enum type{num, op, par_left, par_right};
	ExprToken(const string& s);
	type get_type();
	string get_value();
	int get_operator_priority() const;
	int compare_priority(const ExprToken& token);

private:
	type _type;
	string _value;
};

#endif