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
	vector<ExprToken*>::iterator it;

	for(it = vect.begin(); it < vect.end(); it++){

		if((*it)->get_type() == num){
			//On lit un nombre
			_tokens.push_back(*it);
		}

		else if((*it)->get_type() == op){
			while(!pile.empty() && (*it)->compare_priority(pile.top()) < 0){
				//Tant que le top de la pile a une priorité supérieur ou égale
				_tokens.push_back(pile.top());
				pile.pop();
			}
			pile.push(*it);
		}

		else if((*it)->get_type() == par){
			if( ((TokenPar *) (*it))->is_left_par()){
				//parenthese ouvrante (gauche)
				pile.push(*it);
			}
			else{
				//(*it) est donc une parenthèse droite
				delete (*it); // Nous n'en avons plus besoin
				while(!pile.empty() && !(pile.top()->get_type() == par)){ //vu qu'on empile que des parenthese gauche, pas besoin de test si s'en est une.
					_tokens.push_back(pile.top());
					pile.pop();
					if(pile.empty()){
						//Pas de parenthese ouvrante dans la pile
						cout << "Error Expr constructor : parenthese ouvrante manquante" << endl;
						error();
					}
				}
				ExprToken* tmp = pile.top();
				pile.pop();
				delete tmp;
			}
		}

		else{
			//Type non défini
			cout << "Error Expr constructor : " << (*it)->get_string() << " is not a number, an operator or a parenthese." << endl;
			error();
		}
	}

	while(!pile.empty()){
		//L'entrée est épuisé, on vide la pile
		_tokens.push_back(pile.top());
		pile.pop();
	}
}

Expr::~Expr(){
	vector<ExprToken*>::iterator it;

	for(it = _tokens.begin(); it != _tokens.end(); ++it)
		delete (*it);
}

void Expr::print(){
	vector<ExprToken*>::iterator it;

	for(it = _tokens.begin(); it != _tokens.end(); ++it){
		cout << (*it)->get_string() << " ";
	}
	cout << endl;
}


double Expr::eval(){
	stack<ExprToken*> pile;
	vector<ExprToken*>::iterator it;
	vector<ExprToken*> liste_tmp;
	double res;

	for(it = _tokens.begin(); it != _tokens.end(); ++it)
	{
		if((*it)->get_type() == num)
			pile.push(*it);

		else if((*it)->get_type() == op){
			TokenNum* b = (TokenNum*) pile.top();
			pile.pop();
			TokenNum* a = (TokenNum*) pile.top();
			pile.pop();

			res = ((TokenOp *) *it)->eval(*a, *b);
			//cout << "Opération : " << a->get_string() << " " << ((TokenOp *) *it)->get_string() << " " << b->get_string() << " " << res << endl;

			ExprToken* tmp = new TokenNum(to_string(res));
			liste_tmp.push_back(tmp);

			pile.push(tmp);
		}

		else{
			cout << "Error eval" << endl;
			error();
		}
	}

	double ret = ((TokenNum *) pile.top())->get_number_value();

	for(it = liste_tmp.begin(); it != liste_tmp.end(); ++it)
		delete *it;

	return ret;
}



int main(){
	string str1 = "(17.6-24.1)/4*3+2.49";
	Expr expr = Expr(str1);
	expr.print();
	double res = expr.eval();
	cout << "Résultat : " << res << endl;
}