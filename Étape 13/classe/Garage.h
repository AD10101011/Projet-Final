#ifndef GARAGE_H
#define GARAGE_H

#include <string>
#include <iostream>
#include <cstring>
#include "VecteurTrie.h"
#include "Vecteur.h"
#include "Voiture.h"
#include "Iterateur.h"

using namespace std;

class Garage
{
private:

	VecteurTrie<Employe> employes; // ou Vecteur<Employe>
 	VecteurTrie<Client> clients; // ou Vecteur<Client>
 	Vecteur<Modele> modeles;
 	Vecteur<Option> options;
 	Vecteur<Contrat> contrats;

 	// Le singleton de l'application 

 	static Garage instance;

 	Garage();					// "Personne" ne peut instancier un objet Garage
 	Garage(const Garage&);		// inutile de coder la définition
 								// (sauf si elle est utilisée par la classe Garage)
 								// en private car si en public il ya un probleme d'édition de lien
 								// et aussi car cela indique à l'utilisateur de la calsee qu'il ne peut pas faire de copie
 	Garage & operator=(const Garage&);	// même raison que la copie
 	~Garage();
 	//Le projet de la voiture en cours

 	static Voiture projetEnCours;

public:

	static Garage& getInstance(); // donne accès au singleton
	static Voiture& getProjetEnCours(); // donne accès au projet de voiture en cours
	static void resetProjetEnCours();
	static Employe * employeLogger;
	
/*** Methode Publique  ***/
	void ajouteModele(const Modele &);
	void afficheModelesDisponibles()const;
	Modele getModele(int);
	int nbrElemModeles();

	void ajouteOption(const Option &);
	void afficheOptionsDisponibles()const;
	Option getOption(int);
	int nbrElemOptions();

	void ajouteContrat(const Contrat &);
	Vecteur<Contrat>& getContrat();
	int nbrElemContrat();
	

	void ajouteClient(string,string,string);
	void afficheClients()const;
	void supprimeClientParIndice(int);
	void supprimeClientParNumero(int);
	VecteurTrie<Client>& getClients();

	void ajouteEmploye(string,string,string,string);
	void afficheEmployes()const;
	void supprimeEmployeParIndice(int);
	void supprimeEmployeParNumero(int);
	VecteurTrie<Employe>& getEmployes();


	void importeModeles(string);
	void importeOptions(string);

	void save(ofstream &);
	void load(ifstream &);

	
	
};

#endif