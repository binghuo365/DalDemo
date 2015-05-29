#include "statement.h"

using namespace DAFrame;

CStatement::CStatement()
:_conn(NULL)
{
}

void CStatement::setConnection(CConnection* conn)
{
	_conn = conn;
}

CConnection* CStatement::getConnection()
{
	return _conn;
}
