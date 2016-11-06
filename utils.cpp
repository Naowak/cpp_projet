#include "utils.h"
#include "ExprToken.h"
#include <iostream>
#include <sstream>

using namespace std;

bool is_operator(const string& s){
	return s == "+" || s == "-" || s == "/" || s == "*";
}

bool is_number(const string& s){
	int length = s.length();
	int i = 0;
	for(; i < length; i++)
		if(s[i] < '0' || s[i] > '9')
			return false;
	return true;
}

bool is_parentheses(const string& s){
	return s == "(" || s == ")";
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

vector<ExprToken> split (const string& s, char delim){

	vector <ExprToken> vec;

	stringstream ss;
	ss << s;

	string str;

	
	do{
		getline(ss, str, delim);
		vec.push_back(ExprToken(str));
	}
	while(!ss.eof());

	return vec;
} 

/*int main(){
	string s = "2+6 2* 8 + 9 - 562";
	string t = "2.6* 9 +5 +66";

	cout << set_space(s) << endl;
	cout << set_space(t) << endl;

	return 0;
}*/