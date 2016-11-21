#include <string>
#include <cmath>
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





TokenFunc::TokenFunc(const std::string& s){
	_type = func;
	_value = string(s);
	_name = get_name_from_fun_string(s);

	vector<string> args = get_arguments_from_fun_string(s);
	vector<string>::iterator it;

	for(it = args.begin(); it != args.end(); ++it){
		_arg.push_back(new Expr(*it, not_printed_expr));
	}
}

TokenFunc::~TokenFunc(){
	vector<Expr*>::iterator it;
	for(it = _arg.begin(); it != _arg.end(); ++it)
		delete *it;
}

double TokenFunc::get_number_value() const{
	if(_name == "cos"){
		if(_arg.size() != 1){
			cout << "Error TokenFunc::get_number_value() : cos needs one and only one argument";
			error();
		}
		double arg = _arg.at(0)->eval();
		return cos(arg);
	}
	else if(_name == "sin"){
		if(_arg.size() != 1){
			cout << "Error TokenFunc::get_number_value() : sin needs one and only one argument";
			error();
		}
		double arg = _arg.at(0)->eval();
		return sin(arg);
	}
	else if(_name == "tan"){
		if(_arg.size() != 1){
			cout << "Error TokenFunc::get_number_value() : tan needs one and only one argument";
			error();
		}
		double arg = _arg.at(0)->eval();
		return tan(arg);
	}
	else if(_name == "sqrt"){
		if(_arg.size() != 1){
			cout << "Error TokenFunc::get_number_value() : sqrt needs one and only one argument";
			error();
		}
		double arg = _arg.at(0)->eval();
		return sqrt(arg);
	}
	else if(_name == "log"){
		if(_arg.size() != 1){
			cout << "Error TokenFunc::get_number_value() : log needs one and only one argument";
			error();
		}
		double arg = _arg.at(0)->eval();
		return log(arg);
	}
	else if(_name == "exp"){
		if(_arg.size() != 1){
			cout << "Error TokenFunc::get_number_value() : exp needs one and only one argument";
			error();
		}
		double arg = _arg.at(0)->eval();
		return exp(arg);
	}
	else if(_name == "pow"){
		if(_arg.size() != 2){
			cout << "Error TokenFunc::get_number_value() : pow needs two and only two arguments";
			error();
		}
		double arg = _arg.at(0)->eval();
		double arg2 = _arg.at(1)->eval();
		return pow(arg, arg2);
	}
	else if(_name == "hypot"){
		if(_arg.size() != 2){
			cout << "Error TokenFunc::get_number_value() : hypot needs two and only two arguments";
			error();
		}
		double arg = _arg.at(0)->eval();
		double arg2 = _arg.at(1)->eval();
		return hypot(arg, arg2);
	}
	else if(_name == "lerp"){
		if(_arg.size() != 3){
			cout << "Error TokenFunc::get_number_value() : lerp needs three and only three arguments";
			error();
		}
		double arg = _arg.at(0)->eval();
		double arg2 = _arg.at(1)->eval();
		double arg3 = _arg.at(2)->eval();
		return (1-arg3)*arg + arg3*arg2;
	}
	else if(_name == "polynome"){
		if(_arg.size() < 3){
			cout << "Error TokenFunc::get_number_value() : lerp needs three and only three arguments";
			error();
		}
		int i;
		int size = (int) _arg.at(0)->eval();
		if(_arg.size() != size + 3){
			cout << "Error TokenFunc::get_number_value() : lerp needs three and only three arguments";
			error();
		}
		double x = _arg.at(_arg.size()-1)->eval();;
		double res = 0;
		for(i = 1; i < size+2; ++i)
			res += _arg.at(i)->eval()*pow(x, i-1);
		return res;

	}
	else{
		cout << "Error TokenFunc::get_number_value() : " << _name << " does not exist." << endl;
		error();
	}
	return -1;
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

