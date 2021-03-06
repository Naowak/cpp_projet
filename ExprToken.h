#ifndef __EXPRTOKEN__
#define __EXPRTOKEN__

#include <iostream>
#include <string>
#include <vector>
#include "utils.h"


enum type{op, num, par, id, func};
enum type_par{left, right};



class ExprToken{
public:
	//ExprToken(const std::string& s);
	type get_type();
	std::string get_string();
	int compare_priority(const ExprToken* token);
	virtual int get_priority() const = 0;

protected:
	type _type;
	std::string _value;
};

#include "expr.h"

class TokenValue : public ExprToken {
public:
	int get_priority() const;
	virtual double get_number_value() const = 0;
};



class TokenNum : public TokenValue {
public:
	TokenNum(const std::string& s);
	double get_number_value() const;
private:
	double _number_value;
};



class TokenVar : public TokenValue {
public:
	static Map memory;
	TokenVar(const std::string& s);
	double get_number_value() const;
	double set_number_value(double new_value) const;
};



class TokenFunc : public TokenValue {
public:
	TokenFunc(const std::string& s);
	~TokenFunc();
	double get_number_value() const;
private:
	std::string _name; 
	std::vector<Expr*> _arg;	
};


class TokenOp : public ExprToken {
public:
	TokenOp(const std::string& s);
	int get_priority() const;
	double eval(TokenValue* a, TokenValue* b) const;
};



class TokenPar : public ExprToken {
public:
	TokenPar(const std::string& s);
	int get_priority() const;
	bool is_left_par() const;
};

#endif