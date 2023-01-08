#ifndef OptionException_H
#define OptionException_H
#include "Exception.h"

class OptionException : public Exception
{
private:

public:
	OptionException();
	OptionException(string);
	OptionException(const OptionException &);
	~OptionException();
	
};


#endif