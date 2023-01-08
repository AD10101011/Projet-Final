#include "Client.h"

/*** Constructeur et destructeur ***/

Client::Client():Intervenant()
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur par défaut de Client"<<endl;
	#endif

	setGsm("none");
}

Client::Client(string n , string p , int num , string g):Intervenant(n,p,num)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur d'initialisation de Client"<<endl;
	#endif

	setGsm(g);
}

Client::Client(const Client &c) :  Intervenant(c)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur de copie de Client"<<endl;
	#endif
	setGsm(c.getGsm());
}

Client::~Client()
{
	#ifdef DEBUG
		cout<<"Supression du client ["<<getNom()<<","<<getPrenom()<<"]"<<endl;
	#endif
}

/*** Getters et setters ***/ 

void Client::setGsm(string ngsm)
{
	gsm = ngsm;
}

string Client::getGsm()const
{
	return gsm;
}


/*** Surcharge des opérateurs ***/


Client & Client::operator=(const Client &c)
{

	setNom(c.getNom());
	setPrenom(c.getPrenom());
	setNumero(c.getNumero());
	setGsm(c.getGsm());
	return(*this);
}

/*** Redéfinition de méthode ***/

	string  Client::Tuple()const
	{
		string ch;
		string Num;

		Num = to_string((*this).num);

		ch = Num + ";" + (*this).nom + ";" + (*this).prenom + ";" + (*this).gsm;

		return ch;
	}

	string Client::ToString()const
	{
		string ch;
		string Num;

		Num = to_string((*this).num);

		ch = "[C"+Num+"] "+(*this).nom +" "+(*this).prenom;

		return ch;


	}

/*** Fonctions amies ***/

ostream & operator<<(ostream &s, const Client &c )
{

	s<<endl<<"Nom de du client : "<<c.getNom();
	s<<endl<<"Prénom du client :"<<c.getPrenom();
	s<<endl<<"Num du client : "<<c.getNumero();
	s<<endl<<"Numéro de gsm : "<<c.getGsm();
	return s ;
}

// Methode Load et Save de client

void Client::save(ofstream &fichier)
{
	cout<<"<<save Client>>"<<endl;
	if(fichier.is_open())
	{
		int tailleNom = nom.size();
		int taillePrenom = prenom.size();
		fichier.write((char *)&num,sizeof(int)); 						// Enregistre le numéro de l'employé 
		fichier.write((char *)&tailleNom,sizeof(int));				
		fichier.write((char *)nom.data(),sizeof(char) * tailleNom); 	// Enregistre le nom de l'employé
		fichier.write((char *)&taillePrenom,sizeof(int));
		fichier.write((char *)prenom.data(),sizeof(char) * taillePrenom);  // Enregistre le prénom de l'employé
		int tailleGSM = gsm.size();
		fichier.write((char *)&tailleGSM,sizeof(int));
		fichier.write((char *)gsm.data(),sizeof(char)*tailleGSM);    
	}
}

void Client::load(ifstream &fichier)
{	
	cout<<"<<load Client>>"<<endl;
	if(fichier.is_open())
	{
		//récupère le numéro du client
		fichier.read((char*)&num,sizeof(int));
		// récupère le nom du client
		int tailleNom;
		fichier.read((char *)&tailleNom , sizeof(int));
		nom.resize(tailleNom);
		fichier.read((char *)nom.data(),sizeof(char) * tailleNom);
		// récupère le prénom du client
		int taillePrenom;
		fichier.read((char *)&taillePrenom,sizeof(int));
		prenom.resize(taillePrenom);
		fichier.read((char *)prenom.data(),sizeof(char)*taillePrenom);
		// récupère le numéro de gsm du client
		int tailleGSM;
		fichier.read((char *)&tailleGSM,sizeof(int));
		gsm.resize(tailleGSM);
		fichier.read((char *)gsm.data(),sizeof(char)*tailleGSM);
	}
}