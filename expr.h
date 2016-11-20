#ifndef __EXPR__
#define __EXPR__

#include <iostream>
#include <vector>

#include "ExprToken.h"

class Expr{
	public:
		//Construit une expression à partir du texte
		Expr(const std::string str);
		//Destroy an Expr
		~Expr();
		//Retourne la valeur de l'expression
		double eval();
		//Affiche la représentation interne
		void print();

	private:
		std::vector<ExprToken*> _tokens;
};

#endif