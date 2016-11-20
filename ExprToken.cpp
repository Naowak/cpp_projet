#include <string>
#include "utils.h"
#include "ExprToken.h"

using namespace std;

Map TokenValue::memory;


type ExprToken::get_type(){
	return _type;
}
string ExprToken::get_string(){
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





int TokenValue::get_priority() const{
	cout << "Error : get_priority on TokenValue" << endl;
	error();
	return -1;
}







TokenNum::TokenNum(const std::string& s){
	if(!is_number(s)){
		cout << "Error TokenNum constructor : " << s << " is not a number." << endl;
		error();
	}
	_type = num;
	_value = string(s);
	_number_value = stod(s);
}
double TokenNum::get_number_value() const{
	return _number_value;
}








TokenVar::TokenVar(const std::string& s){
	if(!is_id(s)){
		cout << "Error TokenVar constructor : " << s << " is not an id." << endl;
		error();
	}
	_type = id;
	_value = string(s);
}
double TokenVar::get_number_value() const{
	return TokenValue::memory.get_value(_value);
}
double TokenVar::set_number_value(double new_value) const{
	return TokenValue::memory.set_value(_value, new_value);
}








TokenOp::TokenOp(const std::string& s){
	if(!is_operator(s)){
		cout << "Error : TokenOp constructor : " << s << " is not an operator." << endl;
		error();
	}
	_type = op;
	_value = string(s);
}
int TokenOp::get_priority() const {
	if(_value == "=")
		return 1;
	if(_value == "+" || _value == "-")
		return 2;
	return 3;
}
double TokenOp::eval(TokenValue* a, TokenValue* b) const {
	if(_value == "+")
		return a->get_number_value() + b->get_number_value();
	if(_value == "-")
		return a->get_number_value() - b->get_number_value();
	if(_value == "*")
		return a->get_number_value() * b->get_number_value();
	if(_value == "/")
		return a->get_number_value() / b->get_number_value();
	if(_value == "="){
		return ((TokenVar *) a)->set_number_value(b->get_number_value());
	}
	cout << "Error TokenOp::eval : " << _value << "has not a defined eval" << endl;
	error();
	return 0;
}








TokenPar::TokenPar(const std::string& s){
	if(!is_parentheses(s)){
		cout << "Error TokenPar constructor : " << s << "is not a parenthese." << endl;
		error();
	}
	_type = par;
	_value = string(s);
}
int TokenPar::get_priority() const{
	if(_value == ")"){
		cout << "Error TokenPar::get_priority : on right parenthese." << endl;
		error();
	}
	return -1;
}
bool TokenPar::is_left_par() const{
	return _value == "(";
}

