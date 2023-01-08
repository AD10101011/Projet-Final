#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <iostream> 
#include <fstream>
#include <cstring>
#include "OptionException.h"
using namespace std;

class Option
{
// -------------- Méthodes amies -----------------//

	friend ostream& operator<<(ostream &,const Option &);
	friend istream& operator>>(istream&, Option &);


private:
// -------------- Variable Membre -----------------//

	string code;
	string intitule;
	float prix;

public:
// -------------- Constructeurs -----------------//

	Option();
	Option(string,string,float);
	Option(const Option &);

// -------------- Destructeur -----------------//

	~Option();

// -------------- Setter -----------------//

	void setCode(string c);//throw (OptionException);
	void setIntitule(string);//throw (OptionException);
	void setPrix(float);// throw (OptionException);	

// -------------- Getter -----------------//

	string getCode()const;
	string getIntitule()const;
	float getPrix()const;

// -------------- Opérateur Surchargés -----------------//

	Option operator--();//throw (OptionException);
	Option operator--(int);//throw (OptionException);

// -------------- Méthodes Publique -----------------//

	void Affiche()const;
	void Save(ofstream &)const;
	void Load(ifstream&);
};

#endif