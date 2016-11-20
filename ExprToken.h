#ifndef __EXPRTOKEN__
#define __EXPRTOKEN__

#include <iostream>
#include <string>

enum type{num, op, par};
enum type_par{left, right};



class ExprToken{
public:
	//ExprToken(const std::string& s);
	type get_type();
	std::string get_value();
	int compare_priority(const ExprToken* token);
	virtual int get_priority() const = 0;

protected:
	type _type;
	std::string _value;
};




class TokenNum : public ExprToken {
public:
	TokenNum(const std::string& s);
	int get_priority() const;
	double get_number_value() const;
private:
	double _number_value;
};

class TokenOp : public ExprToken {
public:
	TokenOp(const std::string& s);
	int get_priority() const;
	double eval(TokenNum a, TokenNum b) const;
};

class TokenPar : public ExprToken {
public:
	TokenPar(const std::string& s);
	int get_priority() const;
	bool is_left_par() const;
};

#endif