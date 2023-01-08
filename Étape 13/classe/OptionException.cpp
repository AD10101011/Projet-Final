#include "OptionException.h"

OptionException::OptionException():Exception()
{

}

OptionException::OptionException(string m):Exception(m)
{

}

OptionException::OptionException(const OptionException &o)
{
	setMsg(o.getMsg());
}

OptionException::~OptionException()
{

}