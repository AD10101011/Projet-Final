#ifndef ITERATEUR_H
#define ITERATEUR_H
#include "Vecteur.h"

template <class T>
class Iterateur
{
private:
	const Vecteur<T> &vec;
	T *pCur;

public:
	Iterateur(const Vecteur<T> &v):vec(v),pCur(vec.v){};
	~Iterateur();
	void reset();
	bool end();
	bool operator++();
	bool operator++(int);
	operator T();
	
};

#endif