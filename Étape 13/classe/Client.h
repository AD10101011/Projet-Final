#ifndef Client_H
#define Client_H

#include "Intervenant.h"

class Client : public Intervenant
{
friend ostream & operator<<(ostream & , const Client &);

private:
	string gsm;

public:

	/*** Constructeur et Destructeur ***/
	Client();
	Client(string , string , int , string);
	Client(const Client &);
	~Client();

	/*** Setter et getter ***/

	void setGsm(string);
	string getGsm()const;

	/*** Surcharge d'operateur ***/
	Client & operator=(const Client &);

	/*** Redéfinition des méthodes virtuelles Pure ***/

	string  Tuple()const;
	string ToString()const;

	// Methode Load et save Client

	void save(ofstream&);
	void load(ifstream&);
};
#endif