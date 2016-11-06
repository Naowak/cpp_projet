#ifndef __EXPR__
#define __EXPR__

#include <iostream>
#include <vector>

class Expr{
	public:
		//Construit une expression à partir du texte
		Expr(const std::string str);
		//Retourne la valeur de l'expression
		int eval();
		//Affiche la représentation interne
		void print();

	private:
		std::vector<std::string> _expr;
};

#endif