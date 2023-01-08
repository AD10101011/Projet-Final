#ifndef Intervenant_H
#define Intervenant_H

#include "Personne.h"
#include <fstream>


class Intervenant: public Personne
{
friend ostream & operator<<(ostream & , const Intervenant &);

protected:

	int num;

public:

	// variable statique
	static int numCourant;

	//Constructeur et destructeur 
	Intervenant(); 
	Intervenant(string, string , int);
	Intervenant(const Intervenant &);
	virtual ~Intervenant() = 0;

	/*** Setters et Getters ***/
	void setNumero(int);
	int getNumero()const;

	/*** méthodes virtuelle pure ***/
	virtual string  Tuple() const = 0;
	virtual string ToString() const  = 0;

	/*** Surcharge des opérateurs ***/
	Intervenant & operator=(const Intervenant &);

};
#endif