#ifndef Personne_H
#define Personne_H
using namespace std;
#include <string>
#include <iostream>
#include <cstring>
#include <string.h>


class Personne
{
	friend ostream & operator<<(ostream &, const Personne &);
	friend istream & operator>>(istream &, Personne &);

protected:

	string nom;
	string prenom;

public:

	Personne();
	Personne(string,string);
	Personne(const Personne &);
	~Personne();


	/*** Setters ***/

	void setNom(string);
	void setPrenom(string);

	/*** Getters ***/

	string getNom()const;
	string getPrenom()const;


	/*** Surcharge ***/
	Personne & operator=(const Personne &);
	bool operator>(const Personne &)const;


};


#endif