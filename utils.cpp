#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include "utils.h"
#include "ExprToken.h"

#define REGEX_OPERATOR regex("[+-/*=]")
#define REGEX_NUMBER regex("-?[0-9]+\\.?[0-9]*")
#define REGEX_PARANTHESE regex("[()]")
#define REGEX_ID regex("[a-z]+")
#define REGEX_FUNC regex("[a-z]+\\((([a-z]+|-?[0-9]+\\.?[0-9]*),)*([a-z]|-?[0-9]+\\.?[0-9]*)*\\)")
#define REGEX_SPACE regex("\\s+")

using namespace std;


double Map::set_value(string name, double value){
	vector<double>::iterator itd;
	vector<string>::iterator its;

	for(its = _names.begin(), itd = _values.begin(); its != _names.end(); ++its, ++itd){
		if(*its == name){
			*itd = value;
			return value;
		}
	}
	_names.push_back(name);
	_values.push_back(value);
	return value;
}

double Map::get_value(string name){
	vector<double>::iterator itd;
	vector<string>::iterator its;

	for(its = _names.begin(), itd = _values.begin(); its != _names.end(); ++its, ++itd){
		if(*its == name){
			return *itd;
		}
	}

	cout << "Error Map::get_value : " << name << " has is not initialized" << endl;
	error();
	return -1;
}




bool is_operator(const string& s){
	return regex_match(s, REGEX_OPERATOR);
}

bool is_number(const string& s){
	return regex_match(s, REGEX_NUMBER);
}

bool is_parentheses(const string& s){
	return regex_match(s, REGEX_PARANTHESE);
}

bool is_id(const string& s){
	return regex_match(s, REGEX_ID);
}

bool is_func(const string& s){
	return regex_match(s, REGEX_FUNC);
}


void error(){
	throw exception();
}


string set_space(const string& s){
	string str = string(s);
	string ret;
	smatch res;
	while(!str.empty()){
		//Fonction
		if(regex_search(str, res, REGEX_FUNC, regex_constants::match_continuous))
		{
			ret += res.str() + " ";
			str = str.substr(res.length(), str.length());

		}
		//Variable
		else if(regex_search(str, res, REGEX_ID, regex_constants::match_continuous))
		{
			ret += res.str() + " ";
			str = str.substr(res.length(), str.length());

		}
		//Number
		else if(regex_search(str, res, REGEX_NUMBER, regex_constants::match_continuous))
		{
			ret += res.str() + " ";
			str = str.substr(res.length(), str.length());

		}
		//Paranthèse
		else if(regex_search(str, res, REGEX_PARANTHESE, regex_constants::match_continuous))
		{
			ret += res.str() + " ";
			str = str.substr(res.length(), str.length());

		}
		//Opérateur
		else if(regex_search(str, res, REGEX_OPERATOR, regex_constants::match_continuous))
		{
			ret += res.str() + " ";
			str = str.substr(res.length(), str.length());

		}
		//Espace
		else if(regex_search(str, res, REGEX_SPACE, regex_constants::match_continuous))
		{
			str = str.substr(res.length(), str.length());
		}
		else
		{
			cout << "Error : Synthax Error" << endl;
			break;
		}
	}
	return ret;
}



ExprToken* create_expr_token(const string& s){
	ExprToken* et;
	if(is_number(s))
		et = new TokenNum(s);
	else if(is_id(s))
		et = new TokenVar(s);
	else if(is_operator(s))
		et = new TokenOp(s);
	else if(is_parentheses(s))
		et = new TokenPar(s);
	else if(is_func(s))
		et = new TokenFunc(s);
	else{
		cout << "Error create_expr_token : " << s << " has no type." << endl;
		error();
	}
	return et;
}


string get_name_from_fun_string(const string& s){
	if(!is_func(s)){
		cout << "Error utils :: get_arguments_from_fun_string : " << s << "is not a func" << endl;
	}
	string str = string(s);
	smatch res;
	regex_search(str, res, REGEX_ID, regex_constants::match_continuous);
	return res.str();
}

vector<string> get_arguments_from_fun_string(const string& s){
	if(!is_func(s)){
		cout << "Error utils :: get_arguments_from_fun_string : " << s << "is not a func" << endl;
	}
	string str = string(s);
	vector<string> args;
	smatch res;
	regex_search(str, res, REGEX_ID, regex_constants::match_continuous);
	//On supprime le nom de la fonction
	str = str.substr(res.length(), str.length());
	//On supprime les parantheses
	str = str.substr(1, str.length()-2);
	args = split_in_string(str, ',');
	return args;
}




vector<ExprToken*> split (const string& s, char delim){

	vector <ExprToken*> vec;

	stringstream ss;
	ss << s;

	string str;

	
	do{
		getline(ss, str, delim);
		if(str.length() > 0)
			vec.push_back(create_expr_token(str));
	}
	while(!ss.eof());

	return vec;
}

vector<string> split_in_string (const string& s, char delim){

	vector <string> vec;

	stringstream ss;
	ss << s;

	string str;

	
	do{
		getline(ss, str, delim);
		if(str != "")
			vec.push_back(string(str));
	}
	while(!ss.eof());

	return vec;
}  

