#ifndef VECTEUR_H
#define VECTEUR_H
#include <iostream>
#include "Client.h"
#include "Employe.h"
#include "Modele.h"
#include "Option.h"
#include "Contrat.h"
using namespace std;


template <class T> class Iterateur;

template <class T>
class Vecteur
{
protected:
	T *v;
	int _sizeMax;
	int _size;

public:
	Vecteur();
	Vecteur(int);
	Vecteur(const Vecteur &);
	~Vecteur();

	int size()const;
	int sizeMax()const;
	void Affiche()const;
	void insere(const T &);
	T retire(int);

	Vecteur & operator=(const Vecteur &);
	T & operator[](int);

	friend class Iterateur<T>;
	
};


#endif