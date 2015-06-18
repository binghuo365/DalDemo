#include "connection.h"
#include "connectionimpl.h"
#include "callablestatement.h"

DAFrame::CConnection::~CConnection()
{
	delete _connImpl;
	_connImpl = NULL;
}

DAFrame::CConnection::CConnection()
	:_connImpl(NULL)
{
}

DAFrame::CConnection::CConnection(CConnectionImpl * connImpl)
{
	_connImpl = connImpl;
}

std::auto_ptr< DAFrame::CStatement > DAFrame::CConnection::createStatement()
{
	std::auto_ptr< CStatement > stmt = _connImpl->createStatement();
	stmt->setConnection( this );
	return stmt;
}

std::auto_ptr< DAFrame::CStatement > DAFrame::CConnection::prepareStatement(const char* sql)
{
	std::auto_ptr< CStatement > stmt = _connImpl->prepareStatement( sql );
	stmt->setConnection( this );
	return stmt;
}

 
void DAFrame::CConnection::setAutoCommit(bool autoCommit)
{
	_connImpl->setAutoCommit( autoCommit );
}


bool DAFrame::CConnection::getAutoCommit()
{
	return _connImpl->getAutoCommit();
}

bool DAFrame::CConnection::begin(bool cashed)
{
	return _connImpl->begin();
}


bool DAFrame::CConnection::commit(bool cashed)
{
	return 	_connImpl->commit();
}


bool DAFrame::CConnection::rollback(bool cashed)
{
	return  _connImpl->rollback();
}

bool DAFrame::CConnection::connect()
{
	return _connImpl->connect();
}
bool DAFrame::CConnection::reconnect()
{
	return _connImpl->reconnect();
}
void DAFrame::CConnection::close()
{
	_connImpl->close();
}

 
bool DAFrame::CConnection::isClosed()
{
	return _connImpl->isClosed();
}
    
std::auto_ptr< DAFrame::CCallableStatement > DAFrame::CConnection::prepareCall(const char* sql)
{
	return _connImpl->prepareCall( sql );
}
  
void DAFrame::CConnection::setTransactionIsolation(int level)
{
	_connImpl->setTransactionIsolation( level );
}

bool DAFrame::CConnection::keepActive()
{
	return _connImpl->keepActive();
}

std::auto_ptr<DAFrame::CConnection> DAFrame::CConnection::clone()
{
	DAFrame::CConnection *conn = new DAFrame::CConnection(_connImpl->clone());
	std::auto_ptr<DAFrame::CConnection> autoConn(conn);
	return autoConn;
}

bool DAFrame::CConnection::setEncoding(const char * encode)
{
	return _connImpl->setEncoding( encode );
}

int DAFrame::CConnection::getErrNo() const
{
	return _connImpl->getErrNo();
}

const char * DAFrame::CConnection::getError() const
{
	return _connImpl->getError();
}

/**
* 设置连接
*/
void DAFrame::CConnection::setConnctionImpl(CConnectionImpl *pConnImpl)
{
	_connImpl = pConnImpl;
}
/**
* 得到连接
*/
DAFrame::CConnectionImpl* DAFrame::CConnection::getConnctionImpl()
{
	return _connImpl;
}
