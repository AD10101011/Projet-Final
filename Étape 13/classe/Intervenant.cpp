#include "Intervenant.h"

/*** Constructeur ***/

Intervenant::Intervenant():Personne()
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur par défaut d'intervenant"<<endl;
	#endif
	setNumero(0);
}

Intervenant::Intervenant(string nom, string prenom, int num) : Personne(nom,prenom)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur d'initialisation d'intervenant"<<endl;
	#endif
	setNumero(num);
}

Intervenant::Intervenant(const Intervenant& i) : Personne(i)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur de copie d'intervenant"<<endl;
	#endif

	setNumero(i.getNumero());
}

Intervenant::~Intervenant()
{
	#ifdef DEBUG
		cout<<endl<<"Destructeur d'intervenant"<<endl;
	#endif
}

/*** Setter et getter ***/

void Intervenant::setNumero(int n)
{
	num = n;
}

int Intervenant::getNumero()const
{
	return num;
}

/*** Surcharge d'opérateurs***/

Intervenant & Intervenant::operator=(const Intervenant &i)
{
	
	setNom(i.getNom());
	setPrenom(i.getPrenom());
	setNumero(i.getNumero());
	return (*this);
	
}

/*** Fonctions amies ***/

ostream & operator<<(ostream &s , const Intervenant &i)
{

	s<<endl<<"Nom de l'intervenant: "<<i.getNom();
	s<<endl<<"Prénom de l'intervenant: "<<i.getPrenom();
	s<<endl<<"Num d'intervenant : "<<i.getNumero();

	return s;
}

/*** Déclaration de la variable statique numCourant ***/

int Intervenant::numCourant = 1;