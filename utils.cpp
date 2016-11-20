#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <vector>
#include "ExprToken.h"
#include "utils.h"


using namespace std;

bool is_operator(const string& s){
	return regex_match(s, regex("[+-/*]"));
}

bool is_number(const string& s){
	return regex_match(s, regex("-?[0-9]+\\.?[0-9]*"));
}

bool is_parentheses(const string& s){
	return regex_match(s, regex("[()]"));
}



void error(){
	throw exception();
}



string set_space(const string& s){
	string a;
	char c;
	int i;
	for(i = 0; i < s.length(); i++){
		c = s[i];
		if(c != ' ')
			a += string(1, c);
	}

	string res;
	string tmp;
	bool was_number_or_point = false;
	for(i = 0; i < a.length(); i++){
		c = a[i];
		tmp = string(1, c);
		
		if(is_number(tmp) || tmp == "."){
			if(!was_number_or_point)
				res += " ";
			res += tmp;
			was_number_or_point = true;
		}
		else{
			res += " " + tmp;
			was_number_or_point = false;
		}
	}

	return res;
}

ExprToken* create_expr_token(const string& s){
	ExprToken* et;
	if(is_number(s))
		et = new TokenNum(s);
	else if(is_operator(s))
		et = new TokenOp(s);
	else if(is_parentheses(s))
		et = new TokenPar(s);
	else{
		cout << "Error create_expr_token : " << s << "has no type." << endl;
		error();
	}
	return et;
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
		vec.push_back(string(str));
	}
	while(!ss.eof());

	return vec;
}  

