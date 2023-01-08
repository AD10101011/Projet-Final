#include "Vecteur.h"

template <class T> Vecteur<T>::Vecteur()
{

	_sizeMax = 30;
	_size = 0;
	v = new T[sizeMax()];
}

template <class T> Vecteur<T>::Vecteur(int i)
{
	_sizeMax = i;
	_size = 0 ;
	v = new T[sizeMax()];
}

template <class T> Vecteur<T>::Vecteur(const Vecteur &vec)
{
	_sizeMax = vec.sizeMax();
	_size = vec.size();

	v = new T[sizeMax()];

	for(int i = 0; i<_sizeMax; i++)
	{	
		v[i] = vec.v[i];
	}
}

template <class T> Vecteur<T>::~Vecteur()
{
	delete [] v;
}


/*** Getters ***/


 template <class T> int Vecteur<T>::size()const
{
	return _size;
}

template <class T> int Vecteur<T>::sizeMax()const
{
	return _sizeMax;
}

/*** Fonction d'affichage ***/

template <class T> void Vecteur<T>::Affiche()const
{
	cout<<"[";
	for(int i = 0; i<size();i++)
	{	
		cout<<v[i]<<endl;
		if(i<size()-1)
		{
			cout<<",";
		}
	}
	cout<<"]"<<endl;
}


/*** Fonction d'insertion ***/

template <class T> 
void Vecteur<T>::insere(const T &val)
{
	if(size()>=sizeMax())
		return;

	v[size()] = val;
	_size +=1;
}

/*** Fonction qui permet de retirer ***/
template <class T> 
T Vecteur<T>::retire(int ind)
{
	T temp;

	if(ind>size()-1) return v[0];

	temp = v[ind];

	for(int i=ind; i<size()-1;i++)
	{

		v[i] = v[i+1];
	}

	_size = size() -1;

	return temp;
}

/*** Surcharge d'opérateur ***/
template <class T> Vecteur<T>& Vecteur<T>::operator=(const Vecteur &vec)
{
	if (v != NULL)delete [] v;

	_sizeMax = vec.sizeMax();
	_size = vec.size();

	v = new T[sizeMax()];

	for(int i = 0; i<sizeMax(); i++)
	{	
		v[i] = vec.v[i];
	}

	return (*this);
}


template <class T>
T& Vecteur<T>::operator[](int ind)
{
	return *(v+ind);
}

/*** INSTANCES DES TEMPLATES***/


template class Vecteur<Option>;
template class Vecteur<Modele>;
template class Vecteur<Client>;
template class Vecteur<Employe>;
template class Vecteur<Contrat>;