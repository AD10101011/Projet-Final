#include "Modele.h"


using namespace std;

/*******************************************************************/
/*****Constructeurs et destructeurs********************************/
/*******************************************************************/

Modele::Modele()
{	
	#ifdef DEBUG
	cout<<"Constructeurs par défaut de Modele"<<endl;
	#endif

	nom = NULL;
	setNom("Modele sans nom");
	setPuissance(0);
	setMoteur(Essence);
	setPrixDeBase(0.0f);

}

Modele::Modele(const char *n , int p , Moteur m , float pdb)
{
	#ifdef DEBUG
		cout<<"Constructeurs d'initialisation de Modele ["<<n<<"-"<<p<<"-"<<m<<"-"<<pdb<<"]"<<endl;
	#endif
	nom = NULL;
	setNom(n);
	setPuissance(p);
	setMoteur(m);
	setPrixDeBase(pdb);
}

Modele::Modele(const Modele &source)
{
	#ifdef DEBUG
		cout<<endl<<"-*-Constructeurs de copie de Modele ["<<source.getNom()<<"-"<<source.getPuissance()<<"-"<<source.getMoteur()<<"-"<<source.getPrixDeBase()<<"]-*-"<<endl;
	#endif
	nom = NULL;
	setNom(source.getNom());
	setPuissance(source.getPuissance());
	setMoteur(source.getMoteur());
	setPrixDeBase(source.getPrixDeBase());
	setImage(source.getImage());

}

Modele::~Modele()
{
	#ifdef DEBUG
		cout<<endl<<"-_-_- Destructeur de Modèle de Modele ["<<getNom()<<"-"<<getPuissance()<<"-"<<getMoteur()<<"-"<<getPrixDeBase()<<"]-_-_-"<<endl;
	#endif

	

}

/*******************************************************************/
/*****Getters et Setters********************************************/
/*******************************************************************/


const char * Modele::getNom()const
{
	return nom;
}

int Modele::getPuissance()const
{
	return puissance;
}

Moteur Modele::getMoteur()const
{
	return moteur;
}

float Modele::getPrixDeBase()const
{
	return prixDeBase;
}

string Modele::getImage()const
{
	return image;
}

void Modele::setPuissance(int p)
{

	if(p>=0)
		puissance = p;
}

void Modele::setMoteur(Moteur m)
{
	moteur = m;
}

void Modele::setPrixDeBase(float pdb)
{
	if(pdb>=0)
		prixDeBase = pdb;
}


void Modele::setNom(const char *n)
{	
	if(nom != NULL)
		delete [] nom;
	nom = new char[strlen(n) + 1];
	strcpy(nom,n);
}

void Modele::setImage(string img)
{
	image = img;
}

/*******************************************************************/
/*****Fonctions amies***********************************************/
/*******************************************************************/
istream & operator>>(istream &s,Modele &m)
{
	cout<<endl<<"Entrer le nom :";
	string nom;
	getline(s,nom);

	cout<<endl<<"Entrer la puissance : ";
	int puissance;
	cin>>puissance;

	cout<<endl<<"(1)-->Essence, (2)-->Diesel, (3)-->Electrique, (4)-->Hybride : ";
	int choix;
	cout<<endl<<"Votre choix :";
	cin>>choix;
	Moteur moteur;

	switch(choix)
	{
		case 1:
			moteur = Essence;
			break;

		case 2:
			moteur = Diesel; 
			break;
		
		case 3:
			moteur = Electrique;
			break;
		
		case 4:
			moteur = Hybride;
			break;

	}

	cout<<endl<<"Entrez le prix de base du modèle : ";
	float prixdebase; 
	cin>>prixdebase;

	m.setNom(nom.c_str());
	m.setPuissance(puissance);
	m.setMoteur(moteur);
	m.setPrixDeBase(prixdebase);

	return s;

}

ostream & operator<<(ostream &s , const Modele &m)
{
	s<<"Nom du modèle : "<<m.getNom();
	s<<endl<<"Puissance : "<<m.getPuissance()<<endl<<"Types de moteur : ";

	switch(m.getMoteur())
	{
		case Essence: 
			s<<"Essence";
			break;
		case Diesel:
			s<<"Diesel";
			break;
		case Electrique:
			s<<"Electrique";
			break;
		case Hybride:
			s<<"Hybride";
			break;
	}

	s<<endl<<"Prix de base du modèle : "<<m.getPrixDeBase();

	return s;



}

Modele& Modele::operator=(const Modele &m)
{
	nom = NULL;
	setNom(m.getNom());
	setPuissance(m.getPuissance());
	setMoteur(m.getMoteur());
	setPrixDeBase(m.getPrixDeBase());
	setImage(m.getImage());

	return(*this);
}

/*******************************************************************/
/*****Méthodes Publiques********************************************/
/*******************************************************************/

void Modele::Affiche()const
{
	cout<<nom<<" "<<puissance<<" "<<prixDeBase<<" ";
	switch(moteur)
	{
		case Essence : 
			cout<<"Essence"<<endl;
			break;

		case Diesel : 
			cout<<"Diesel"<<endl;
			break;

		case Electrique : 
			cout<<"Electrique"<<endl;
			break;

		case Hybride : 
			cout<<"Hybride"<<endl;
			break;
	}
} 

void Modele::Save(ofstream& fichier) const
{
  int nomLength = strlen(getNom());
  int tailleImage = image.size();
  cout << "<<Save  (Modele)>>" << endl;
 
  if(fichier.is_open())
  {
    fichier.write((char*)&nomLength, sizeof(int));
    fichier.write((char*)nom, sizeof(char) * strlen(getNom()));
    fichier.write((char*)&puissance, sizeof(int));
    fichier.write((char*)&moteur, sizeof(enum Moteur));
    fichier.write((char*)&prixDeBase, sizeof(float));
    fichier.write((char*)&tailleImage,sizeof(int));
		fichier.write((char*)image.data(),sizeof(char)*tailleImage);
  }
}

void Modele::Load(ifstream& fichier)
{
  int nomLength;
  int tailleImage;

  cout << "<<Load (Modele)>>" << endl;

  if(fichier.is_open())
  {
    fichier.read((char*)&nomLength, sizeof(int));
    delete [] nom;
    nom = new char[nomLength];
    fichier.read((char*)nom, sizeof(char) * nomLength);
    fichier.read((char*)&puissance, sizeof(int));
    fichier.read((char*)&moteur, sizeof(enum Moteur));
    fichier.read((char*)&prixDeBase, sizeof(float)); 
    fichier.read((char*)&tailleImage,sizeof(int));
		image.resize(tailleImage);
		fichier.read((char*)image.data(),sizeof(char)*tailleImage);
  }

}