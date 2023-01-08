#include "Employe.h"

const string Employe::ADMINISTRATIF = "Administratif";
const string Employe::VENDEUR = "Vendeur";

/*** Constructeur et Destructeur ***/

Employe::Employe():Intervenant()
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur par défaut d'employe"<<endl;
	#endif
	setLogin("none");
	resetMotDePasse();
	setFonction("none");
}

Employe::Employe(string nom , string prenom , int num , string login ,string fonction):Intervenant(nom,prenom,num)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur d'initialisation d'employe"<<endl;
	#endif
	
	setLogin(login);
	setFonction(fonction);
	resetMotDePasse();
}

Employe::Employe(const Employe &e)
{
	#ifdef DEBUG
		cout<<endl<<"Constructeur de Copie d'employe"<<endl;
	#endif

	setNom(e.getNom());
	setPrenom(e.getPrenom());
	setNumero(e.getNumero());
	setLogin(e.getLogin());
	if(e.MotDePasse != NULL) setMotDePasse(e.getMotDePasse());
	setFonction(e.getFonction());
}

Employe::~Employe()
{
	#ifdef DEBUG
	cout<<"Supression de l'employé ["<<getNom()<<","<<getPrenom()<<"]"<<endl;
	#endif

	resetMotDePasse();
}

/*** Setters et Getters ***/

void Employe::setLogin(string l)
{
	#ifdef DEBUG
		cout<<endl<<"<<SETTER setLogin>>"<<endl;
	#endif
	login = l;
}

void Employe::resetMotDePasse()
{
	#ifdef DEBUG
		cout<<endl<<"<<Methode resetMotDePasse>>"<<endl;
	#endif

	if (MotDePasse!=NULL)
	{
		delete MotDePasse;
		MotDePasse = NULL;
	}
}

void Employe::setMotDePasse(string mdp) //throw (PasswordException)
{
	#ifdef DEBUG
		cout<<endl<<"<<SETTER setMotDePasse>>"<<endl;
	#endif
	
	int digit = 0 , alpha = 0;

	if (mdp.length()<6)
	{
		throw PasswordException(PasswordException::INVALID_LENGTH);
	}

	for(int i=0; i<mdp.length();i++)
	{
		if(((int)mdp[i] >= 65 && (int)mdp[i] <= 90) || ((int)mdp[i] >=97 && (int)mdp[i]<=122))
		{
			alpha = 1 ;
		}

		if((int)mdp[i] >= 48 && (int)mdp[i] <= 57)
		{
			digit = 1 ;
		}
	}

	if (alpha == 0)
	{
		throw PasswordException(PasswordException::ALPHA_MISSING);
	}

	if (digit == 0)
	{
		throw PasswordException(PasswordException::DIGIT_MISSING);
	}

	if(!MotDePasse);
		MotDePasse = new string;

	*MotDePasse = mdp;
}

void Employe::setFonction(const string f)
{
	#ifdef DEBUG
		cout<<endl<<"<<SETTER setFonction>>"<<endl;
	#endif
	fonction = f;
}

string Employe::getLogin()const
{
	return login;
}

string Employe::getMotDePasse()const //throw (PasswordException)
{
	if (!MotDePasse)
	{
		throw PasswordException(PasswordException::NO_PASSWORD);	
	}
	
	return *MotDePasse;
}

string Employe::getFonction()const
{
	return fonction;
}

/*** Redéfinition de méthodes ***/


Employe & Employe::operator=(const Employe &e)
{
	#ifdef DEBUG
		cout<<endl<<"<<opérateur = >>"<<endl;
	#endif

	setNom(e.getNom());
	setPrenom(e.getPrenom());
	setNumero(e.getNumero());
	setLogin(e.getLogin());
	if(e.MotDePasse != NULL)
		setMotDePasse(e.getMotDePasse());
	setFonction(e.getFonction());

	return(*this);
}

/*** Méthode amies ***/

ostream & operator<<(ostream &s, const Employe &e)
{
	#ifdef DEBUG
		cout<<endl<<"<<opérateur '<<' >>"<<endl;
	#endif
	s<<endl<<"Nom de l'employé : "<<e.getNom();
	s<<endl<<"Prénom de l'employé:"<<e.getPrenom();
	s<<endl<<"Num de l'employé: "<<e.getNumero();
	s<<endl<<"Login de l'employé :"<<e.getLogin();

	if (e.MotDePasse != NULL)
		s<<endl<<"MotDePasse de l'employé : "<<e.getMotDePasse();
	else
		s<<endl<<"MotDePasse de l'employé : [/]";
	
	s<<endl<<"Fonction de l'employé : "<<e.getFonction();
	return s ;
}

string  Employe::Tuple()const
{
	#ifdef DEBUG
		cout<<endl<<"<<Méthode Tuple>>"<<endl;
	#endif
	string ch;
	string Num;
	
	Num = to_string((*this).num);
	ch = Num + ";" + (*this).nom + ";" + (*this).prenom + ";" + (*this).fonction;

	return ch;

}

string Employe::ToString()const
{
	#ifdef DEBUG
		cout<<endl<<"<<Méthode ToString>>"<<endl;
	#endif

	string ch;
	string Num;

	Num = to_string((*this).num);

	if ((*this).fonction == "Vendeur")
	{
		ch = "[V" + Num + "]" + (*this).nom + (*this).prenom ;
	}
	else
	{
		ch = "[A" + Num + "]" + (*this).nom + (*this).prenom ;
	}

	return ch;


}

void Employe::save(ofstream & fichier) // Écriture d'un employé dans le fichier passé en paramètre
{
	cout<<"<<save Employe>>"<<endl;
	if(fichier.is_open())
	{
		if(num != 0)
		{
			fichier.write((char *)&num,sizeof(int));						// Enregistre le numéro de l'employé 
		
			int tailleNom = nom.size();
			fichier.write((char *)&tailleNom,sizeof(int));				
			fichier.write((char *)nom.data(),sizeof(char) * tailleNom); 	// Enregistre le nom de l'employé
			
			int taillePrenom = prenom.size();
			fichier.write((char *)&taillePrenom,sizeof(int));
			fichier.write((char *)prenom.data(),sizeof(char) * taillePrenom);  // Enregistre le prénom de l'employé
			
			int tailleLogin = login.size();
			fichier.write((char *)&tailleLogin,sizeof(int));
			fichier.write((char *)login.data(),sizeof(char)*tailleLogin);	// Enregistre le login de l'employé
			
			int verif;

			if(MotDePasse == NULL)
			{	
				verif = 0;
				fichier.write((char *)&verif,sizeof(int));
			}
			else
			{
				verif = 1;
				fichier.write((char *)&verif,sizeof(int));
				int tailleMotDePasse = MotDePasse->size();
				fichier.write((char *)&tailleMotDePasse,sizeof(int));
				string mdp = *MotDePasse;
				fichier.write((char *)mdp.data(),sizeof(char)*tailleMotDePasse); // Enregistre le mot de passe de l'employé
			}

			int tailleFonction = fonction.size();
			fichier.write((char *)&tailleFonction,sizeof(int));
			fichier.write((char *)fonction.data(),sizeof(char) * tailleFonction); //Enregistre la fonction de l'employé 
				
		}
		
	}
}

void Employe::load(ifstream &fichier) // Lecture d'un employé dans le fichier passé en paramètre.
{
	cout<<"<<load Employe>>"<<endl;
	if(fichier.is_open())
	{
		//récupère le numéro de l'employé
		fichier.read((char*)&num,sizeof(int));
		
		// récupère le nom de l'employé
		int tailleNom;
		fichier.read((char *)&tailleNom , sizeof(int));
		nom.resize(tailleNom);
		fichier.read((char *)nom.data(),sizeof(char) * tailleNom);
		
		// récupère le numéro de l'employé
		int taillePrenom;
		fichier.read((char *)&taillePrenom,sizeof(int));
		prenom.resize(taillePrenom);
		fichier.read((char *)prenom.data(),sizeof(char)*taillePrenom);
		
		// récupère le login de l'employé
		int tailleLogin;
		fichier.read((char *)&tailleLogin,sizeof(int));
		login.resize(tailleLogin);
		fichier.read((char *)login.data(),sizeof(char)*tailleLogin);
		
		//récupère le mot de passe
		int verif;
		fichier.read((char *)&verif,sizeof(int));
		if(verif == 1)
		{
			int tailleMotDePasse;
			string mdp;
			fichier.read((char *)&tailleMotDePasse,sizeof(int));
			mdp.resize(tailleMotDePasse);
			fichier.read((char *)mdp.data(),sizeof(char)*tailleMotDePasse);
			MotDePasse = new string(mdp);
		}

		//récupère la fonction de l'employé
		int tailleFonction;
		fichier.read((char *)&tailleFonction,sizeof(int));
		fonction.resize(tailleFonction);
		fichier.read((char *)fonction.data(),sizeof(char) * tailleFonction);
	}
}