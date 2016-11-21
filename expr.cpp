#include <stack>
#include <string>
#include "utils.h"
#include "ExprToken.h"
#include "expr.h"


using namespace std;

Expr::Expr(const string& str, type_expr te){
	string s = set_space(str);
	vector<ExprToken*> vect = split(s, ' ');
	stack<ExprToken*> pile;
	vector<ExprToken*>::iterator it;



	for(it = vect.begin(); it < vect.end(); it++){

		if((*it)->get_type() == num){
			//On lit un nombre
			_tokens.push_back(*it);
		}

		else if((*it)->get_type() == id){
			//On lit une var
			_tokens.push_back(*it);
		}

		else if((*it)->get_type() == func){
			//On lit une fonction
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
				delete *it; // Nous n'en avons plus besoin
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

	//On indique à chaque expression si elle a été indiqué comme printed ou pas.
	_type_expr = te;
}

Expr::~Expr(){
	vector<ExprToken*>::iterator it;

	for(it = _tokens.begin(); it != _tokens.end(); ++it)
		delete *it;
}

void Expr::print() const{
	vector<ExprToken*>::const_iterator it;

	for(it = _tokens.begin(); it != _tokens.end(); ++it){
		cout << (*it)->get_string() << " ";
	}
	cout << endl;
}


double Expr::eval() const{
	stack<ExprToken*> pile;
	vector<ExprToken*>::const_iterator it;
	vector<ExprToken*> liste_tmp;
	double res;

	for(it = _tokens.begin(); it != _tokens.end(); ++it)
	{
		if((*it)->get_type() == num)
			pile.push(*it);

		else if((*it)->get_type() == id)
			pile.push(*it);

		else if((*it)->get_type() == func)
			pile.push(*it);

		else if((*it)->get_type() == op){
			TokenValue* b = (TokenValue*) pile.top();
			pile.pop();
			TokenValue* a = (TokenValue*) pile.top();
			pile.pop();

			res = ((TokenOp *) *it)->eval(a, b);
			//cout << "Opération : " << a->get_string() << " " << ((TokenOp *) *it)->get_string() << " " << b->get_string() << " " << res << endl;

			ExprToken* tmp = new TokenNum(to_string(res));
			liste_tmp.push_back(tmp);

			pile.push(tmp);
		}

		else{
			cout << "Error eval : " << (*it)->get_string() << " non reconize" << endl;
			cout << "Type is : " << (*it)->get_type() << endl;
			error();
		}
	}

	double ret = 0;

	if(!pile.empty()){
		TokenValue* tmp = (TokenValue *) pile.top();
		ret = tmp->get_number_value();
	}

	for(it = liste_tmp.begin(); it != liste_tmp.end(); ++it)
		delete *it;

	return ret;
}

bool Expr::is_printed() const{
	return _type_expr == printed_expr;
}



/*int main(){
	string str1 = "(17.6-24.1)/4*3+2.49";
	Expr expr = Expr(str1, printed_expr);
	expr.print();
	double res = expr.eval();
	cout << "Résultat : " << res << endl;
}*/