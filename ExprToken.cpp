#include "utils.h"
#include "ExprToken.h"
#include <string>

ExprToken::ExprToken(const string& s){
	if(is_number(s)){
		_type = num;
		_value = string(s);
	}
	else if(is_operator(s)){
		_type = op;
		_value = string(s);
	}
	else if(is_parentheses(s)){
		if(s == "(")
			_type = par_left;
		else
			_type = par_right;
		_value = string(s);
	}
	else
		cout << "Error constructor" << endl;
}

ExprToken::type ExprToken::get_type(){
	return _type;
}

string ExprToken::get_value(){
	return _value;
}

/* If this is an operator, return 0 if its value is + or -, 1 if it is / or *.
Return -1 if it's not an operator */
int ExprToken::get_operator_priority() const{
	if(_type == op){
		if(_value == "-" || _value == "+")
			return 1;
		return 2;
	}
	else if(_type == par_left){
		return 0;
	}
	cout << "Error get_operator_priority" << endl;
	return -1;
}


int ExprToken::compare_priority(const ExprToken& token){
	int v1 = this->get_operator_priority();
	int v2 = token.get_operator_priority();
	if(v1 > v2)
		return 1;
	else if(v1 == v2)
		return 0;
	return -1;
}