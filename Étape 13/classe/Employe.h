#ifndef EMPLOYE_H
#define EMPLOYE_H
#include "Intervenant.h"
#include "PasswordException.h"

class Employe : public Intervenant
{

	friend ostream & operator<<(ostream & , const Employe &);

protected:



	string login;
	string *MotDePasse = NULL;
	string fonction;

public:


	static const string ADMINISTRATIF;
	static const string VENDEUR;

	/*** Constructeurs et Destructeur ***/
	Employe();
	Employe(string,string,int,string,string);
	Employe(const Employe &);
	~Employe();

	/*** Setters et Getters ***/
	void setLogin(string);
	void setMotDePasse(string); //throw (PasswordException);
	void setFonction(string);
	void resetMotDePasse();

	string getLogin()const;
	string getMotDePasse()const; //throw (PasswordException);
	string getFonction()const;


	/*** Redéfinition des méthodes***/

	Employe & operator=(const Employe &);
	string  Tuple()const;
	string ToString()const;
	

	/*** Méthode Save et Load ***/
	void save(ofstream &); // Enregistre un employe sur disque
	void load(ifstream &); // Lit un employe sur disque
	
};

#endif