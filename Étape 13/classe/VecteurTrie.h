#ifndef VECTEURTRIE_H
#define VECTEURTRIE_H

#include "Vecteur.h"

template <class T> class Iterateur;

template <class T> 
class VecteurTrie : public Vecteur <T>
{

private:

public:

	VecteurTrie();
	VecteurTrie(int t);
	~VecteurTrie();

	void insere(const T&);
	friend class Iterateur<T>;
	
};



#endif