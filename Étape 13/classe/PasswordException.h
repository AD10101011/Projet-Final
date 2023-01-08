#ifndef PASSWORDEXCEPTION_H
#define PASSWORDEXCEPTION_H
#include "Exception.h"

class PasswordException : public Exception
{

protected:
	int code;

public:
	PasswordException();
	PasswordException(int);
	PasswordException(const PasswordException &);
	~PasswordException();

	void setCode(int);
	int getCode()const;


	static const int INVALID_LENGTH;
	static const int DIGIT_MISSING;
	static const int ALPHA_MISSING;
	static const int NO_PASSWORD;
	
};


#endif