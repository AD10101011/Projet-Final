#include "Voiture.h"
/*******************************************************************/
/*****Constructeurs et destructeurs********************************/
/*******************************************************************/
Voiture::Voiture()
{
	int i ;

	#ifdef DEBUG
		cout<<"Constructeurs par défaut de Voiture"<<endl;
	#endif

	setNom("Voiture sans nom");
	Modele modele();
	
	for(i=0;i<5;i++)
	{
		option[i] = NULL;
	}
}
Voiture::Voiture(string n , Modele m)
{
	#ifdef DEBUG
		cout<<"Constructeurs d'initialisation de voiture"<<endl;
	#endif

	setNom(n);
	setModele(m);

	for(int i=0;i<5;i++)
	{
		option[i] = NULL;
	}
}
Voiture::Voiture(const Voiture &v)
{
	#ifdef DEBUG
		cout<<"Constructeurs de copie de Voiture"<<endl;
	#endif
	setNom(v.getNom());
	setModele(v.getModele());

	for(int i = 0; i < 5 ; i++)
    {
        if(v.option[i] != NULL)
        {
            option[i] = new Option(*v.option[i]);
        }
        else
        {
            option[i] = NULL;
        }
    }
}
Voiture::~Voiture()
{
	#ifdef DEBUG
		cout<<endl<<"-_-_- Destructeur de Voiture :"<<getNom()<<"-_-_-"<<endl;
	#endif

	for(int i = 0; i<5; i++)
	{
		if(option[i] != NULL)
			RetireOption(option[i]->getCode());
	}
}
/*******************************************************************/
/*****Getters et Setters********************************************/
string Voiture::getNom()const
{
	return nom;
}
Modele Voiture::getModele()const
{
	return modele;
}
void Voiture::setNom(string n)
{	
	#ifdef DEBUG
		cout<<"Méthode setNom Voiture"<<endl;
	#endif

	nom = n;
}
void Voiture::setModele(const Modele &m)
{
	modele.setNom(m.getNom());
	modele.setPuissance(m.getPuissance());
	modele.setMoteur(m.getMoteur());
	modele.setPrixDeBase(m.getPrixDeBase());
	modele.setImage(m.getImage());
}
/*******************************************************************/
/*****Surcharge des opérateurs**************************************/
/*******************************************************************/
Voiture & Voiture::operator=(const Voiture &v)
{
	setNom(v.getNom());
	setModele(v.getModele());

	for(int i=0;i<5;i++)
	{	
		delete option[i];
		option[i]=NULL;

		if(v.option[i] != NULL)
		{	
			AjouteOption(*(v.option[i]));
		}	
	}
	return (*this);
}
Voiture Voiture::operator+(const Option &o)//throw (OptionException)
{
	Voiture v(*this);
	v.AjouteOption(o);
	return v;
}
Voiture Voiture::operator-(const Option &o)
{
	Voiture v(*this);
	v.RetireOption(o.getCode());
	return v;
}
Voiture Voiture::operator-(string c)
{
	Voiture v(*this);
	v.RetireOption(c);
	return v;
}
int Voiture::operator<(const Voiture &v)
{
	if (getPrix()<v.getPrix()) 
		return 1;
	else
		return 0;
}
int Voiture::operator>(const Voiture &v)
{
	if (getPrix()>v.getPrix()) 
		return 1;
	else 
		return 0;
}
int Voiture::operator==(const Voiture &v)
{
	if (getPrix()==v.getPrix()) 
		return 1;
	else
		return 0;
}
Option * Voiture::operator[](int i)
{
	return option[i];
}
/*******************************************************************/
/*****Fonction amie*************************************************/
/*******************************************************************/
Voiture operator+(const Option &o,const Voiture &v)//throw (OptionException)
{
	Voiture v1(v);
	v1.AjouteOption(o);
	return v1;
}

ostream & operator<<(ostream &s, const Voiture &v)
{
	// s<<"Nom de la voiture : "<<v.getNom()<<endl;
	// Modele m;
	// m = v.getModele();

	// s<<"Modèle de la voiture : ["<<m.getNom()<<","<<m.getPuissance()<<","<<m.getMoteur()<<","<<m.getPrixDeBase()<<"]"<<endl;

	v.Affiche();
	return s ;
}
/*******************************************************************/
/*****Méthodes Publiques********************************************/
/*******************************************************************/

void Voiture::AjouteOption(const Option &o)//throw (OptionException)
{
	int i = 0;
	Option * op;

	for(i=0;option[i]!=NULL && i<5 ;i++);

	if (i == 5)
	{
		OptionException e("\t-->Le nombre maximum d'option a déjà été atteint '*'max(5)'*' !");
		throw e;
	}

	for(i=0;i<5;i++)
	{
		if(option[i] != NULL && option[i]->getCode() == o.getCode())
		{
			OptionException e("\t-->Vous tentez d'ajoutez une option déjà présente !");
			throw e ;
		}
	}

	for(i=0;i<5;i++)
	{
		if (option[i] == NULL)
		{	
			op = new Option(o);
			option[i] = op;
			i = 5;
		}
	}
}

float Voiture::getPrix()const
{
	int s = 0;

	for(int i=0;i<5;i++)
	{
		if(option[i] != NULL)
		{
			s = s + (option[i])->getPrix();
		}
	}

	s = s + modele.getPrixDeBase();

	return s ;
}

void Voiture::RetireOption(string c)//throw (OptionException)
{

	int i = 0 , booleen = 0;

	for(i=0;i<5;i++)
	{
		if(option[i] != NULL && option[i]->getCode() == c)
		{
			i = 5;
			booleen = 1;
		}
	}

	if (booleen == 0)
	{
		OptionException e("\t-->Vous tentez de retirer une option qui n'existe pas !");
		throw e;
	}

	for(i=0;i<5;i++)
	{
		if(option[i] != NULL)
		{
			if((option[i])->getCode() == c)
			{
				delete option[i];
				option[i] = NULL;
				i+=5;
			}
		}
	}
}

void Voiture::Affiche() const
{

	cout<<"Nom du projet: "<<nom<<endl;
	modele.Affiche();
	
	for(int i=0;i<5;i++)
	{

		if (option[i] != NULL)
		{
			option[i]->Affiche();
		}
		else
			cout<<endl<<"[/]"<<endl;

	}
	
}


void Voiture::Save()const
{

	cout<<"<<Voiture : Save >>"<<endl;


	int i , cpt;
	int tailleNom = nom.size();

	string nomProjet = nom + ".car";

	for(i = 0 , cpt = 0; i<5; i++)
	{
		if(option[i] != NULL)
		{
			cpt++;
		}
	}

	ofstream fichier1("Fichier Car/" + nomProjet,ios::out);

	if(fichier1.is_open())
	{	
		fichier1.write((char*)&tailleNom,sizeof(int));
		fichier1.write((char*)nom.data(),sizeof(char)*tailleNom);

		modele.Save(fichier1);

		fichier1.write((char*)&cpt, sizeof(int));
		

		for(int i=0;i<5;i++)
		{	
			if(option[i] != NULL)option[i]->Save(fichier1);
		}

		fichier1.close();
	}
}

void Voiture::Load(string NomFichier)
{


	cout<<"<< Voiture : Load >>"<<endl;

	int tailleNom, i ,cpt;
	Option OptionTmp;

	for(i=0; i<5;i++)
	{
		if(option[i] != NULL)
		{	
			RetireOption(option[i]->getCode());
		}
	}

	ifstream fichier2("Fichier Car/" + NomFichier,ios::in);

	if(fichier2.is_open())
	{	
		fichier2.read((char*)&tailleNom,sizeof(int));

		nom.resize(tailleNom);
		fichier2.read((char*)nom.data(),sizeof(char)*tailleNom);

		modele.Load(fichier2);

		fichier2.read((char*)&cpt,sizeof(int));

		for(i = 0; i<cpt; i++)
		{
			OptionTmp.Load(fichier2);
			AjouteOption(OptionTmp);
		}

		fichier2.close();
	}

	
}