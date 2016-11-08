#include "expr.h"
#include "ExprToken.h"
#include "utils.h"
#include <stack>
#include <string>

using namespace std;

Expr::Expr(const string str){
	string s = set_space(str);
	vector<ExprToken*> vect = split(s, ' ');
	stack<ExprToken*> pile;
	vector<string> out;
	vector<ExprToken*>::iterator it;

	for(it = vect.begin(); it < vect.end(); it++){

		if((*it)->get_type() == num)
			out.push_back((*it)->get_value());

		else if((*it)->get_type() == op){
			while(!pile.empty() && (*it)->compare_priority(pile.top()) < 0){ //pile.top() rtourne 0x0
				out.push_back(pile.top()->get_value());
				pile.pop();
			}
			pile.push(*it);
		}

		else if((*it)->get_type() == par){
			if((*it)->get_value() == "("){
				pile.push(*it);
			}
			else{
				//(*it) est donc une parenthèse droite
				while(!pile.empty() && !(pile.top()->get_type() == par)){ //vu qu'on empile que des parenthese gauche, pas besoin de test si s'en est une.
					out.push_back(pile.top()->get_value());
					pile.pop();
					if(pile.empty()){
						cout << "Error : parenthese ouvrante manquante" << endl;
						error();
					}
				}
				pile.pop();
			}
		}

		else{
			cout << "Error : " << (*it)->get_value() << " is not a number or an operator." << endl;
			error();
		}
	}

	while(!pile.empty()){
		out.push_back(pile.top()->get_value());
		pile.pop();
	}

	_expr = out;
}

void Expr::print(){
	vector<string>::iterator it;

	for(it = _expr.begin(); it != _expr.end(); it++){
		cout << *it << " ";
	}
	cout << endl;
}


int Expr::eval(){
	stack<string> pile;
	vector<string>::iterator it;

	for(it = _expr.begin(); it != _expr.end(); it++)
	{
		if(is_number(*it))
			pile.push(*it);
		else if(is_operator(*it)){
			int a = stoi(pile.top());
			pile.pop();
			int b = stoi(pile.top());
			pile.pop();
			int res;

			if(*it == "+")
				res = b + a;
			else if(*it == "-")
				res = b - a;
			else if(*it == "*")
				res = b * a;
			else if(*it == "/")
				res = b / a;

			pile.push(to_string(res));
		}
		else{
			cout << "Error eval" << endl;
			error();
		}
	}

	return stoi(pile.top());
}



int main(){
	string str1 = "(17-24)/4*3+2";
	Expr expr = Expr(str1);
	expr.print();
	int res = expr.eval();
	cout << "Résultat : " << res << endl;
}