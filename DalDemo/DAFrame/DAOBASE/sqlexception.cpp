#include "sqlexception.h"

using namespace DAFrame;

CSQLException::CSQLException(int errorCode , const char* desc)
:CException(desc , ExceptionCodeDB ),_SQLError(errorCode , desc)
{

}

CSQLException::~CSQLException() throw()
{

}

const char* CSQLException::what() const
{
	return _SQLError.getSQLDesc().c_str();
}

const CSQLError& CSQLException::getSQLError()
{
	return _SQLError;
}