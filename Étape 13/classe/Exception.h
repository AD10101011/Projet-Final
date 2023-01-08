#ifndef EXCEPTION_H
#define EXCEPTION_H
using namespace std;
#include <string>
#include <iostream>

class Exception
{
protected:

	string msg;

public:
	Exception();
	Exception(string);
	Exception(const Exception &);
	~Exception();
	
	void setMsg(string);
	string getMsg()const;
};

#endif