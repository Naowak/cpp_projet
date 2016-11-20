#ifndef __EXPR__
#define __EXPR__

#include <iostream>
#include <vector>

#include "ExprToken.h"

enum type_expr{printed_expr, not_printed_expr};

class Expr{
	public:
		//Construit une expression à partir du texte
		Expr(const std::string& str, type_expr te);
		//Destroy an Expr
		~Expr();
		//Retourne la valeur de l'expression
		double eval();
		//Affiche la représentation interne
		void print();
		//Est il demander que le résultat s'affiche ?
		bool is_printed();

	private:
		std::vector<ExprToken*> _tokens;
		type_expr _type_expr;
};

#endif