#ifndef Voiture_H
#define Voiture_H

#include "Modele.h"
#include "Option.h"
#include "OptionException.h"
#include <string>
#include <cstring>
#include<iostream>
using namespace std;

class Voiture 
{
// -------------- Méthodes amies -----------------//
	friend Voiture operator+(const Option &o , const Voiture &v);// throw (OptionException);
	friend ostream & operator<<(ostream &,const Voiture &);

private:
// -------------- Variable Membre -----------------//
	string nom;
	Modele modele;
	Option * option[5];

public:
// -------------- Constructeurs -----------------//
	Voiture();
	Voiture(string,Modele);
	Voiture(const Voiture &);

// -------------- Destructeur -----------------//
	~Voiture();

// -------------- Setter -----------------//
	void setNom(string);
	void setModele(const Modele &);

// -------------- Getter -----------------//
	string getNom()const;
	Modele getModele()const;
	float getPrix()const;

// -------------- Méthodes Publique -----------------//
	void Affiche()const;
	void RetireOption(string); //throw (OptionException);
	void AjouteOption(const Option &);// throw (OptionException);
	void Load(string);
	void Save()const;


// -------------- Opérateur Surchargés -----------------//
	Voiture & operator=(const Voiture &);
	Voiture operator+(const Option &);//throw (OptionException);
	Voiture operator-(const Option &);
	Voiture operator-(string);
	int operator<(const Voiture &);
	int operator>(const Voiture &);
	int operator==(const Voiture &);
	Option * operator[](int);

};

#endif