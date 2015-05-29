#include "exception.h"
#include <string.h>

using namespace DAFrame;

CNullHandleException::CNullHandleException(const char* file , int line )
:CException()
{
	std::ostringstream str;
	str << "CNullHandleException " << file << "(" << line << ")";
	_str = str.str();
}
CNullHandleException::~CNullHandleException()
{
}

