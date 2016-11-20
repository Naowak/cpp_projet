#ifndef __SEQEXPR__
#define __SEQEXPR__

#include <iostream>
#include <vector>
#include "expr.h"

class seqExpr{
public:
	//Construit une expression à partir d'un texte
	seqExpr(const std::string str);
	//destroy an seqExpr
	~seqExpr();
	//Calcul et affiche les valeurs des expressions dans la sequence
	void eval();
	//Affiche les expressions
	void print();

private:
	std::vector<Expr*> _seqExpr;
};

#endif