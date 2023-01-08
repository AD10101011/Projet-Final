#include "Garage.h"

/*** Constructeur et Destructeur ***/



Garage::Garage()
{
	#ifdef DEBUG 
		cout<<endl<<"Constructeur par defaut de Garage"<<endl;
	#endif

	employes.insere(Employe("ADMIN","ADMIN",0,"admin",Employe::ADMINISTRATIF));
}

Garage::~Garage()
{
	#ifdef DEBUG
		cout<<endl<<"Destructeur de Garage"<<endl;
	#endif
	if (employeLogger != NULL) 
	{
		delete employeLogger;
		employeLogger = NULL;
	}
}

/*** Méthode Publique***/

void Garage::ajouteModele(const Modele &m)
{	
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode ajoutdeModele>>"<<endl;
	#endif

	if(modeles.size() < modeles.sizeMax())
	{
		modeles.insere(m);
	}
}

void Garage::afficheModelesDisponibles()const
{
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode afficheModelesDisponibles>>"<<endl;
	#endif
	modeles.Affiche();
}

Modele Garage::getModele(int indice)
{
	return modeles[indice];
}

void Garage::ajouteOption(const Option &o)
{
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode ajouteOption>>"<<endl;
	#endif

	if(options.size() < options.sizeMax())
	{
		options.insere(o);
	}
}

void Garage::afficheOptionsDisponibles()const
{
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode afficheOptionsDisponibles>>"<<endl;
	#endif
	options.Affiche();
}

Option Garage::getOption(int indice)
{
	return options[indice];
}


void Garage::ajouteContrat(const Contrat &c)
{
	if(contrats.size()<contrats.sizeMax())
	{
		contrats.insere(c);
		Contrat::numCourant++;
	}

}

Vecteur<Contrat>& Garage::getContrat()
{
	return contrats;
}


void Garage::ajouteClient(string nom,string prenom,string gsm)
{
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode ajouteClient>>"<<endl;
	#endif

	if(clients.size() < clients.sizeMax())
	{
		clients.insere(Client(nom,prenom,Intervenant::numCourant,gsm));
		Intervenant::numCourant++;
	}
}

void Garage::afficheClients()const
{
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode afficheClients>>"<<endl;
	#endif

	clients.Affiche();
}


void Garage::ajouteEmploye(string nom,string prenom,string login,string fonction)
{
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode ajouteEmploye>>"<<endl;
	#endif

	if(employes.size() < employes.sizeMax())
	{
		employes.insere(Employe(nom,prenom,Intervenant::numCourant,login,fonction));
		Intervenant::numCourant++;
	}
	
}

void Garage::afficheEmployes()const
{
	#ifdef DEBUG 
		cout<<endl<<"<<Méthode afficheEmployes>>"<<endl;
	#endif

	employes.Affiche();
}


void Garage::supprimeClientParIndice(int ind)
{
	clients.retire(ind);
}

void Garage::supprimeClientParNumero(int numero)
{
	int i ;
	Iterateur<Client> it(clients);
	for(i = 0 ,it.reset(); !it.end() && ((Client)it).getNumero() != numero ;it++ ,i++);
	if(clients[i].getNumero() == numero) clients.retire(i);
	
}

void Garage::supprimeEmployeParIndice(int ind)
{
	employes.retire(ind);
}

void Garage::supprimeEmployeParNumero(int numero)
{
	int i ;
	Iterateur<Employe> it(employes);
	for(i = 0 ,it.reset(); !it.end() && ((Employe)it).getNumero() != numero ;it++ ,i++);
	if(employes[i].getNumero() == numero) employes.retire(i);
	
}



// Récupérer l'instance de Garage;

Garage& Garage::getInstance()
{
	return instance;
}

// Récupérer l'instance du Projet en cours de Voiture

Voiture& Garage::getProjetEnCours()
{
	return projetEnCours;
}

// reset le projet en cours de Voiture

void Garage::resetProjetEnCours()
{
	Garage::projetEnCours=Voiture();
}


void Garage::importeModeles(string nomFichier) // permet d'importer des modèles du fichier CSV dans Garage
{
	ifstream fichier(nomFichier,ios::in);
	string buffer;
	
	if(fichier.is_open())
	{	int i = 0;
		while(getline(fichier,buffer))
		{	
			Modele m;
			char phrase[200];
			strcpy(phrase,buffer.c_str());

			m.setNom(strtok(phrase,";"));
			
			m.setPuissance(atoi(strtok(NULL,";")));

			string moteur = strtok(NULL,";");

			if(moteur == "essence")
			{
				m.setMoteur((enum Moteur) 0);
			}
			if(moteur == "diesel")
			{
				m.setMoteur((enum Moteur) 1);
			}
			if(moteur == "electrique")
			{
				m.setMoteur((enum Moteur) 2);
			}
			if(moteur == "hybride")
			{
				m.setMoteur((enum Moteur) 3);
			}

			m.setImage(strtok(NULL,";"));

			m.setPrixDeBase(atof(strtok(NULL,"")));

			ajouteModele(m);

		}
		fichier.close(); // Fermeture du fichier
	}

}

void Garage::importeOptions(string nomFichier)
{
	ifstream fichier(nomFichier,ios::in);
	string buffer;
	Option o;

	if(fichier.is_open())
	{	
		while(getline(fichier,buffer))
		{
			char phrase[200];
			strcpy(phrase,buffer.c_str());
			try
			{
				o.setCode(strtok(phrase,";"));
				o.setIntitule(strtok(NULL,";"));
				o.setPrix(atof(strtok(NULL,"")));
				ajouteOption(o);

			}
			catch(OptionException e )
			{
				cout<<e.getMsg();
			}

		}

		fichier.close();
	}
	else
		cout<<"Erreur ouverture fichier !"<<endl;
	
}

int Garage::nbrElemOptions()
{
	return options.size();
}

int Garage::nbrElemModeles()
{
	return modeles.size();
}

int Garage::nbrElemContrat()
{
	return contrats.size();
}


VecteurTrie<Employe>& Garage::getEmployes()
{
	return employes;
}

VecteurTrie<Client>& Garage::getClients()
{
	return  clients;
}


// Méthode Load et Save

void Garage::save(ofstream &fichier)
{
	cout << "<<save garage>>"<<endl;
	if(fichier.is_open())
	{
		// Enregistre le numCourant d'employe;
		fichier.write((char *)&Intervenant::numCourant,sizeof(int));

		int nbr = employes.size() - 1;
		fichier.write((char *)&nbr,sizeof(int)); // enregistre le nombre d'employé existant
		
		Iterateur<Employe>itE(employes);
		for(itE.reset();!itE.end();itE++)
		{
			Employe e = (Employe)itE;
			e.save(fichier); // Enregistre toute les informations relatives au employé
		}
		nbr = clients.size();
		fichier.write((char *)&nbr,sizeof(int)); // Enregistre le nombre de client existant

		if(nbr!=0)
		{
			Iterateur<Client>itC(clients);
			for(itC.reset();!itC.end();itC++)
			{
				Client c = (Client)itC;
				c.save(fichier); // Enregistre toutes les informations relative au client
			}
		}

		fichier.write((char*)&Contrat::numCourant,sizeof(int)); // Enregistre le numCourant de Contrat

		nbr = contrats.size();
		fichier.write((char *)&nbr,sizeof(int)); // Enregistre le nombre de contrats

		if(nbr!=0)
		{
			Iterateur<Contrat>itC(contrats);
			for(itC.reset();!itC.end();itC++)
			{
				Contrat c((Contrat)itC);
				c.Save(fichier); // Enregistre toutes les informations relative au client
			}
		}
	}	
}

void Garage::load(ifstream &fichier)
{
	cout<<"<<load garage>>"<<endl;

	if(fichier.is_open())
	{
		//récupère le numCourant d'employé
		fichier.read((char *)&Intervenant::numCourant,sizeof(int));
		// récupère le nombre d'employés présent dans le fichier.
		int nbrEmploye;
		fichier.read((char *)&nbrEmploye,sizeof(int));
		// récupère chaques employés et l'insère dans le vecteurs d'employés
		for(int i = 0; i<nbrEmploye;i++)
		{
			Employe e;
			e.load(fichier);
			employes.insere(e);
				
		}
		// récupère le nombre de client présent dans le fichier et insère les clients dans le bon vecteur.
		int nbrClient;
		fichier.read((char *)&nbrClient,sizeof(int));
		for(int i = 0; i<nbrClient; i++)
		{
			Client c;
			c.load(fichier);
			clients.insere(c);
		}

		fichier.read((char *)&Contrat::numCourant,sizeof(int)); // Récupère le numCourant de Contrat

		int nbrContrat;
		fichier.read((char *)&nbrContrat,sizeof(int));
		for(int i=0; i<nbrContrat;i++)
		{
			Contrat c;
			c.Load(fichier);
			
			Iterateur<Employe>itE(employes);
			for(itE.reset();!itE.end() && c.getVendeur()->getNumero() != ((Employe)itE).getNumero();itE++);
			if(c.getVendeur()->getNumero() == ((Employe)itE).getNumero())
			{
				c.setVendeur((Employe)itE);
			}
			Iterateur<Client>itC(clients);
			for(itC.reset();!itC.end() && c.getClient()->getNumero() != ((Client)itC).getNumero();itC++);
			if(c.getClient()->getNumero() == ((Client)itC).getNumero())
			{
				c.setClient((Client)itC);
			}
			contrats.insere(c);
		}
	}
}


// instance du garage

Garage Garage::instance=Garage();

//instance du projet en cours de Voiture

Voiture Garage::projetEnCours=Voiture();

// variable statique de l'employé connecté

Employe * Garage::employeLogger = NULL;
