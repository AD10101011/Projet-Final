#include "Personne.h"

/*******************************************************************/
/*****Constructeurs et destructeurs********************************/
/******************************************************************/

Personne::Personne()
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur par défaut de Personne"<<endl;
	#endif

	setNom("UNKNOW");
	setPrenom("UNKNOW");
}

Personne::Personne(string n , string p)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur d'initialisation de Personne"<<endl;
	#endif

	setNom(n);
	setPrenom(p);
}

Personne::Personne(const Personne &p)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur de Copie"<<endl;
	#endif
		
	setNom(p.getNom());
	setPrenom(p.getPrenom());
}

Personne::~Personne()
{
	#ifdef DEBUG
	cout<<" Destruceur de Personne :["<<getNom()<<","<<getPrenom()<<"]"<<endl;
	#endif
}


/******************************************************************/
/*****Setters********************************/
/******************************************************************/

void Personne::setNom(string n)
{
	nom = n;
}

void Personne::setPrenom(string p)
{
	prenom = p;
}

/******************************************************************/
/*****Getters******************************************************/
/******************************************************************/

string Personne::getNom()const
{
	return nom;
}

string Personne::getPrenom()const
{
	return prenom;
}

/******************************************************************/
/*****Surcharge des opérateurs ************************************/
/******************************************************************/

/*** membre ***/

Personne & Personne::operator=(const Personne &p)
{
	setNom(p.getNom());
	setPrenom(p.getPrenom());

	return (*this);
}

bool Personne::operator>(const Personne &p)const
{

	if(this->getNom() > p.getNom())
	{
		return 1;
	}
	if(this->getNom() == p.getNom())
	{
		if(this->getPrenom() > p.getPrenom())
		{
			return 1 ;
		}

		return 0;
	}

	return 0;
}


/*** amis ***/

ostream & operator<<(ostream &s , const Personne &p)
{

	s<<endl<<"Nom de la personne : "<<p.getNom();
	s<<endl<<"Prenom de la personne :"<<p.getPrenom();
	return s;
}


istream & operator>>(istream &s, Personne &p)
{
	string name;
	cout<<endl<<"Entrer votre nom :";
	getline(cin,name);

	string surname;
	cout<<endl<<"Entrer votre prenom :";
	getline(cin,surname);

	p.setNom(name);
	p.setPrenom(surname);

	return s;
}



