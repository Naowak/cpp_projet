#include "utils.h"
#include "ExprToken.h"
#include <string>

using namespace std;

type ExprToken::get_type(){
	return _type;
}

string ExprToken::get_value(){
	return _value;
}


int ExprToken::compare_priority(const ExprToken* token){
	int v1, v2;

	v1 = this->get_priority();
	v2 = token->get_priority();
	if(v1 > v2)
		return 1;
	else if(v1 == v2)
		return 0;
	return -1;
}





TokenNum::TokenNum(const std::string& s){
	if(!is_number(s)){
		cout << "Error " << s << " is not a number." << endl;
		error();
	}
	_type = num;
	_value = string(s);
	_number_value = stoi(s);
}

int TokenNum::get_priority() const{
	cout << "Error get_priority on num" << endl;
	error();
	return -1;
}

int TokenNum::get_number_value() const{
	return _number_value;
}




TokenOp::TokenOp(const std::string& s){
	if(!is_operator(s)){
		cout << "Error : " << s << " is not an operator." << endl;
		error();
	}
	_type = op;
	_value = string(s);
}

int TokenOp::get_priority() const {
	if(_value == "+" || _value == "-")
		return 1;
	return 2;
}

int TokenOp::eval(TokenNum a, TokenNum b) const {
	if(_value == "+")
		return a.get_number_value() + b.get_number_value();
	if(_value == "-")
		return a.get_number_value() - b.get_number_value();
	if(_value == "*")
		return a.get_number_value() * b.get_number_value();
	if(_value == "/")
		return a.get_number_value() / b.get_number_value();
	cout << "Error" << _value << "has not a defined eval" << endl;
	error();
	return 0;
}



TokenPar::TokenPar(const std::string& s){
	if(!is_parentheses(s)){
		cout << "Error : " << s << "is not a parenthese." << endl;
		error();
	}
	_type = par;
	_value = string(s);
}

int TokenPar::get_priority() const{
	if(_value == ")")
		cout << "Error : token_par get_priority on right parenthese." << endl;
	return 0;
}

bool TokenPar::is_left_par() const{
	return _value == "(";
}