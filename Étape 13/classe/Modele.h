#ifndef MODEL_H
#define MODEL_H
#include<iostream> 
#include<string>  
#include <fstream> 
#include <cstring>  

using namespace std;
// -------------- énumération -----------------//

enum Moteur {Essence, Diesel, Electrique, Hybride};

class Modele
{
// -------------- Méthodes amies -----------------//

	friend ostream& operator<<(ostream &,const Modele &);
	friend istream& operator>>(istream &,Modele &);

private:
// -------------- Variable Membre -----------------//

	char *nom; 
	int puissance;
	Moteur moteur;
	float prixDeBase;
	string image;
	
public:
// -------------- Constructeurs -----------------//

	Modele();
	Modele(const char *, int , Moteur , float);
	Modele(const Modele &);
// -------------- Destructeur -----------------//

	~Modele();

// -------------- Getter -----------------//

	const char * getNom()const;
	int getPuissance()const;
	Moteur getMoteur()const;
	float getPrixDeBase()const;
	string getImage()const;

// -------------- Setter -----------------//

	void setNom(const char *);
	void setPuissance(int);
	void setMoteur(Moteur);
	void setPrixDeBase(float);
	void setImage(string);

// -------------- Opérateur Surchargés -----------------//

	Modele& operator=(const Modele &);

// -------------- Méthodes Publique -----------------//
	
	void Affiche()const; 

	void Save(ofstream &)const;
	void Load(ifstream &);



};



#endif