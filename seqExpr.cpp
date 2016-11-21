#include <iostream>
#include <vector>
#include <string>
#include "utils.h"
#include "expr.h"
#include "seqExpr.h"

using namespace std;

seqExpr::seqExpr(const std::string str){
	vector<string> split_endl = split_in_string(str, '\n');
	vector<string>::iterator it_endl;
	vector<string>::iterator it_semi;

	Expr* tmp;

	//On cherche maintenant si dans chaque morceau du split précédent, 
	//il n'y pas un plusieurs morceaux séparé par des ;
	for(it_endl = split_endl.begin(); it_endl != split_endl.end(); ++it_endl){
		vector<string> split_semi = split_in_string(*it_endl, ';');

		//Le dernier est fini par un \n, les autres par des ;
		for(it_semi = split_semi.begin(); it_semi != split_semi.end(); ++it_semi){
			if(next(it_semi) == split_semi.end()){
				tmp = new Expr(*it_semi, printed_expr);
				_seqExpr.push_back(tmp);
			}
			else{
				tmp = new Expr(*it_semi, not_printed_expr);
				_seqExpr.push_back(tmp);
			}
		}
	}
}

seqExpr::~seqExpr(){
	vector<Expr*>::iterator it;
	for(it = _seqExpr.begin(); it != _seqExpr.end(); ++it)
		delete *it;
}

void seqExpr::eval(){
	vector<Expr*>::iterator it;
	double res;

	for(it = _seqExpr.begin(); it != _seqExpr.end(); ++it){
		res = (*it)->eval();
		if((*it)->is_printed())
			cout << res << endl;
	}
}

void seqExpr::print(){
	vector<Expr*>::iterator it;

	for(it = _seqExpr.begin(); it != _seqExpr.end(); ++it){
		(*it)->print();
	}
}

int main(){
	string str1 = "(17.6-24.1)/4*3+2.49\n869;8.23*96-5/4.569";//59*7+6;53/8\n56-9\n2-3;5*9";
	string str2 = "var = (5 + 9) *7;second = 2;var * second / 3 + 4";
	string str3 = "5 + 2 + cos(5)";

	seqExpr sexpr = seqExpr(str3);
	sexpr.print();
	cout << endl << "Resultats : " << endl;
	sexpr.eval();

	return 0;
}
