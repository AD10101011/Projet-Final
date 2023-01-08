#include "VecteurTrie.h"


template <class T>
VecteurTrie<T>::VecteurTrie():Vecteur<T>()
{
	#ifdef DEBUG
		cout<<"Constructeur par défaut du Vecteur"<<endl;
	#endif

}
template <class T>
VecteurTrie<T>::VecteurTrie(int t):Vecteur<T>(t)
{
	#ifdef DEBUG
		cout<<"Constructeur d'initialisation du Vecteur"<<endl;
	#endif
}

template <class T>
VecteurTrie<T>::~VecteurTrie()
{
	#ifdef DEBUG
		cout<<"Destructeur de VecteurTrie"<<endl;
	#endif
}

template <class T>
void VecteurTrie<T>::insere(const T& val)
{
	int i , pos;

	if(this->size() >= this->sizeMax())
		return;

	for(i = 0; i < this->size() && val > this->v[i]; i++);
	pos = i;
	
	this->_size++;

	for(i=this->size() - 1; i>=pos; i--)
	{	
		this->v[i+1] = this->v[i];
	}

	this->v[pos] = val;
	
	
}

template class VecteurTrie<Client>;
template class VecteurTrie<Employe>; 