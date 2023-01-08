#include "Contrat.h"


Contrat::Contrat()
{
	vendeur = NULL;
	client = NULL;
	setNum(0);
	setNomProjet("UNKNOW");

}

Contrat::Contrat(Employe vend, Client cl, int n, string nom)
{
	vendeur = NULL;
	client = NULL;
	setVendeur(vend);
	setClient(cl);
	setNum(n);
	setNomProjet(nom);
}

Contrat::Contrat(const Contrat& c)
{	
	vendeur = NULL;
	client = NULL;
	if(c.vendeur != NULL) setVendeur(*(c.getVendeur()));
	if(c.client != NULL ) setClient(*(c.getClient()));
	setNum(c.getNumContrat());
	setNomProjet(c.getNomProjet());
}

Contrat::~Contrat()
{
	#ifdef DEBUG2
		cout<<"Destructeur de Contrat"<<endl;
	#endif

	if(vendeur != NULL)
		delete vendeur;
	if(client != NULL)
		delete client;

}

void Contrat::setNum(int n)
{
	num = n;
}

int Contrat::getNumContrat()const
{
	return num;
}

void Contrat::setNomProjet(string p)
{
	nomProjet = p;
}

string Contrat::getNomProjet()const
{
	return nomProjet;
}

void Contrat::setVendeur(const Employe &vend)
{
	if(vendeur != NULL)
		delete vendeur;

	vendeur = new Employe(vend);
}

Employe * Contrat::getVendeur()const
{
	return vendeur;
}

void Contrat::setClient(const Client &cl)
{
	if(client != NULL)
		delete client;

	client = new Client(cl);
}

Client * Contrat::getClient()const
{
	return client;
}


// Surcharge des opérateurs
Contrat & Contrat::operator=(const Contrat& c)
{
	setVendeur(*(c.getVendeur()));
	setClient(*(c.getClient()));
	setNum(c.getNumContrat());
	setNomProjet(c.getNomProjet());

	return(*this);
}

string Contrat::Tuple()const
{
	string ch ;
	ch = to_string(num) + ";" + vendeur->getNom() +" "+vendeur->getPrenom() + ";" + client->getNom() +" "+client->getPrenom() + ";" + nomProjet;
	return ch;
}

ostream & operator<<(ostream &s,const Contrat &c)
{
	s<<endl<<"Numéro de contrat :"<<c.getNumContrat()<<endl<<"Nom du vendeur : "<<c.vendeur->getNom()<<endl<<"Nom du Client:"<<c.client->getNom()<<endl<<"Nom du projet : "<<c.getNomProjet()<<endl;
	return s;
}

// Méthode Load et Save de Contrat

void Contrat::Save(ofstream &fichier)
{
	cout<<"<<Save de Contrat>>"<<endl;
	if(fichier.is_open())
	{
		int n;

		fichier.write((char *)&num,sizeof(int));

		n = vendeur->getNumero();
		fichier.write((char *)&n,sizeof(int)); // Numéro du vendeur
		n = client->getNumero();

		fichier.write((char *)&n,sizeof(int)); // Numéro du client

		n = nomProjet.size();
		fichier.write((char *)&n,sizeof(int)); // Taille du nom du projet
		fichier.write((char *)nomProjet.data(),sizeof(char)*n);// Nom du projet
	}
}	



void Contrat::Load(ifstream &fichier)
{	
	cout<<"<<Load de Contrat>>"<<endl;
	if(fichier.is_open())
	{
		// récupération info vendeur
		int numero;
		fichier.read((char *)&num,sizeof(int));
		fichier.read((char *)&numero,sizeof(int)); // Numéro du vendeur
		vendeur = new Employe;
		vendeur->setNumero(numero);
		
		// récupération info client
		fichier.read((char *)&numero,sizeof(int)); // Numéro du client
		client = new Client;
		client->setNumero(numero);

		// récupération nom projet
		int taille;
		string chaine;
		fichier.read((char*)&taille,sizeof(int));
		chaine.resize(taille);
		fichier.read((char *)chaine.data(),sizeof(char)*taille);
		nomProjet = chaine;

	}
}

// Variable statique

int Contrat::numCourant = 1;