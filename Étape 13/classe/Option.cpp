
#include "Option.h"

/*******************************************************************/
/*****Constructeurs et destructeurs********************************/
/*******************************************************************/

Option::Option()
{
	#ifdef DEBUG
	cout<<"<Constructeurs par défaut d'option>"<<endl;
	#endif

	setCode("XXXX");

	setIntitule("sans nom");

	setPrix(0.0f);
}

Option::Option(string c, string i , float p)
{
	#ifdef DEBUG
	cout<<"<Constructeurs d'initialisation d'option>"<<endl;
	#endif

	setCode(c);
	setIntitule(i);
	setPrix(p);

}

Option::Option(const Option &source)
{
	#ifdef DEBUG
	cout<<endl<<"-*-Constructeurs de copie d'option ["<<source.getCode()<<" "<<source.getIntitule()<<" "<<source.getPrix()<<"]-*-"<<endl;
	#endif

	setCode(source.getCode());
	setPrix(source.getPrix());
	setIntitule(source.getIntitule());
}

Option::~Option()
{
	#ifdef DEBUG
		cout<<endl<<"-_-_-Destructeur d'option : ["<<getCode()<<" "<<getIntitule()<<" "<<getPrix()<<"]-_-_-"<<endl;
	#endif
}

/*******************************************************************/
/*****Getters et Setters********************************************/
/*******************************************************************/
void Option::setPrix(float p) //throw (OptionException)
{	

	if (p < 0)
	{
		OptionException e("Le prix de l'option ne peut pas être négatif ! ");
		throw e;
	}
	prix = p;

}

void Option::setIntitule(string i)//throw (OptionException)
{
	if (i.length() == 0)
	{
		OptionException e("vous avez saisis un mauvais intitulé !");
		throw e;
	}

	intitule = i;
}

void Option::setCode(string c)//throw (OptionException)
{	
	if (c.length() != 4)
	{
		OptionException e("Code incorrecte ! ");
		throw e;
	}


	code = c;
}

string Option::getCode()const
{
	return code;
}

string Option::getIntitule()const
{
	return intitule;
}

float Option::getPrix()const
{

	return prix;
}
/*******************************************************************/
/*****Surcharge d'opérateurs****************************************/
/*******************************************************************/

Option Option::operator--()//throw (OptionException)
{	
	if(((*this).getPrix() - 50) < 0)
	{
		OptionException e("Vous tentez de retirer une somme supérieur au prix de l'option !");
	}
	(*this).setPrix((*this).getPrix() - 50);
	return(*this);
}

Option Option::operator--(int)//throw (OptionException)
{	
	if(((*this).getPrix() - 50) < 0)
	{
		OptionException e("Vous tentez de retirer une somme supérieur au prix de l'option !");
	}

	Option temp(*this);
	(*this).setPrix((*this).getPrix() - 50);
	return temp;
}


/*******************************************************************/
/*****Fonctions amies***********************************************/
/*******************************************************************/

ostream& operator<<(ostream&s, const Option &o)
{
	s<<endl<<"Code de l'option : "<<o.getCode()<<endl;
	s<<"Intitulé de l'option : "<<o.getIntitule()<<endl;
	s<<"Prix de l'option : "<<o.getPrix()<<endl;

	return s;
}

istream& operator>>(istream&s, Option &o)
{
	cout<<endl<<"Code de l'option : ";
	string c;
	getline(cin,c);
	o.setCode(c);

	cout<<endl<<"Intitulé de l'option : ";
	string i;
	getline(cin,i);
	o.setIntitule(i);

	cout<<endl<<"Prix de l'option :";
	float p;
	cin>>p;
	o.setPrix(p);

	return s;
}

/*******************************************************************/
/*****Méthodes Publiques********************************************/
/*******************************************************************/

void Option::Affiche()const
{	
	#ifdef DEBUG
		cout<<"<Méthode Publique Affiche()>"<<endl;
	#endif

	cout<<"Code de l'option : "<<code<<endl<<"Intitulé : "<<intitule<<endl<<"Prix : "<<prix<<endl;
}

void Option::Save(ofstream &fichier)const
{

	cout<<"<<Option : Save >>"<<endl;


	int tailleCode = getCode().size();
	int tailleIntitule = getIntitule().size();

	if(fichier.is_open())
	{

		fichier.write((char*)&tailleCode,sizeof(int));
		fichier.write((char*)getCode().data(),sizeof(char) * tailleCode);

		fichier.write((char*)&tailleIntitule,sizeof(int));
		fichier.write((char*)getIntitule().data(),sizeof(char) * tailleIntitule);

		fichier.write((char*)&prix,sizeof(float));

	}
}

void Option::Load(ifstream &fichier)
{	

	cout<<"<< Option : Load >>"<<endl;


	int tailleCode;
	int tailleIntitule;

	if(fichier.is_open())
	{
		fichier.read((char*)&tailleCode,sizeof(int));
		intitule.resize(tailleCode);
		fichier.read((char*)code.data(),sizeof(char)*tailleCode);

		fichier.read((char*)&tailleIntitule,sizeof(int));
		intitule.resize(tailleIntitule);
		fichier.read((char*)intitule.data(),sizeof(char)*tailleIntitule);

		fichier.read((char*)&prix,sizeof(float));

	}
}