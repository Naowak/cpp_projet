#ifndef __EXPR__
#define __EXPR__

#include <iostream>
#include <vector>

using namespace std;

class Expr{
	public:
		//Construit une expression à partir du texte
		Expr(const string str);
		//Retourne la valeur de l'expression
		int eval();
		//Affiche la représentation interne
		void print();

	private:
		vector<string> _expr;
};

#endif