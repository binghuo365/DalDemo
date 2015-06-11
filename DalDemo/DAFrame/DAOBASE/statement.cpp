#include "statement.h"

using namespace DAFrame;

DAFrame::CStatement::CStatement() : _conn(NULL)
{

}

void DAFrame::CStatement::setConnection(CConnection* conn)
{
	_conn = conn;
}

DAFrame::CConnection* DAFrame::CStatement::getConnection()
{
	return _conn;
}
