#include "PasswordException.h"

PasswordException::PasswordException():Exception()
{

}

PasswordException::PasswordException(int c):Exception()
{
	code = c;

	switch(code)
	{
		case 1:
			msg = "INVALID_LEGTH -- Le mdp doit contenir au min 6 caractère !";
			break;

		case 2:
			msg = "DIGIT_MISSING -- Votre mot de passe doit contenir au moins 1 chiffre !";
			break;
		case 3:
			msg = "ALPHA_MISSING -- Votre mot de passe doit contenir au moins 1 lettre !";
			break;
		case 4:
			msg = "NO_PASSWORD -- L'employé ne possède aucun mot de passe !";
			break;
		default:

			msg = "Erreur inconnue lors de la saisie du mot de passe !";
	}


}

PasswordException::PasswordException(const PasswordException &c):Exception(c)
{
	setCode(c.getCode());
}

PasswordException::~PasswordException()
{

}

void PasswordException::setCode(int c)
{
	code = c;
}

int PasswordException::getCode()const
{
	return code;
}


const int PasswordException::INVALID_LENGTH = 1;
const int PasswordException::DIGIT_MISSING = 2;
const int PasswordException::ALPHA_MISSING = 3;
const int PasswordException::NO_PASSWORD = 4;