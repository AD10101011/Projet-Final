#ifndef CONTRAT_H
#define CONTRAT_H

#include <string>
#include <iostream>
#include "Employe.h"
#include "Client.h"
using namespace std;

class Contrat
{
	//Surcharge des opérateur ami

	friend ostream & operator<<(ostream & , const Contrat &); // permet d'afficher le contrat

private: 
	// variable membre

	Employe * vendeur; // pointeur qui récupère l'employé actuellement connecté
	Client * client;   // poiteur qui récupère le client pour qui le contrat est créé
	int num;           // numéro du contrat
	string nomProjet;  // nom du projet associé au contrat
public:

	static int numCourant; // numéro de contrat unique pour toute les instances de contrat

	// Constructeur

	Contrat();
	Contrat(Employe , Client , int , string);
	Contrat(const Contrat&);

	// Destructeur

	~Contrat();

	// Setter et Getter

	void setVendeur(const Employe &);
	Employe * getVendeur()const;

	void setClient(const Client &);
	Client * getClient()const;

	void setNum(int n);
	int getNumContrat()const;

	void setNomProjet(string);
	string getNomProjet()const;


	// Surcharge des opérateur membre
	Contrat& operator=(const Contrat&); // Permet de copier un contrat

	// Save et Load de Contrat

	void Save(ofstream &); // Sauvegarde toutes les données liées au contrat
	void Load(ifstream &); // Charge toutes les données liées au contrat
	
	// autre méthodes

	string Tuple()const; // Crée un tuple (num;N. P. (Employé);N. P. (Client))
};

#endif