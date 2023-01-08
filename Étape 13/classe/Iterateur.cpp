#include "Iterateur.h"

template <class T>
Iterateur<T>::~Iterateur()
{

}

template <class T>
void Iterateur<T>::reset()
{
	pCur = vec.v;
}

template <class T>
bool Iterateur<T>::end()
{
	if(pCur - vec.v >= vec._size) return true;
	else return false;
}

template <class T>
bool Iterateur<T>::operator++()
{
	if(!end())
	{	
		pCur++;
		return true;
	}

	return false;
}

template <class T>
bool Iterateur<T>::operator++(int)
{
	return operator++();
}

template <class T>

Iterateur<T>::operator T()
{
	return *pCur;
}

template class Iterateur<Employe>;
template class Iterateur<Client>;
template class Iterateur<Contrat>;