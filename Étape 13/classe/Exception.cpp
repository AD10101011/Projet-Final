#include "Exception.h"

Exception::Exception()
{
	msg = "aucun message d'erreur";
}

Exception::Exception(string m)
{
	setMsg(m);
}

Exception::Exception(const Exception &e)
{
	setMsg(e.getMsg());
}

Exception::~Exception()
{
	
}

void Exception::setMsg(string m)
{
	msg = m;
}

string Exception::getMsg()const
{
	return msg;
}

