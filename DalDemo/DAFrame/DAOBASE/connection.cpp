#include "connection.h"

using namespace DAFrame;

CConnection::~CConnection()
{
	delete _connImpl;
	_connImpl = NULL;
	
	delete _transaction;
	_transaction = NULL;
}

CConnection::CConnection()
	:_connImpl(NULL)
{
}

CConnection::CConnection(CConnectionImpl * connImpl)
{
	_connImpl = connImpl;
}

std::auto_ptr< CStatement > CConnection::createStatement()
{
	std::auto_ptr< CStatement > stmt = _connImpl->createStatement();
	stmt->setConnection( this );
	return stmt;
}

std::auto_ptr< CStatement > CConnection::prepareStatement(const char* sql)
{
	std::auto_ptr< CStatement > stmt = _connImpl->prepareStatement( sql );
	stmt->setConnection( this );
	return stmt;
}

 
void CConnection::setAutoCommit(bool autoCommit)
{
	_connImpl->setAutoCommit( autoCommit );
}


bool CConnection::getAutoCommit()
{
	return _connImpl->getAutoCommit();
}

bool CConnection::begin(bool cashed)
{
	bool b = _connImpl->begin();
	if( b && cashed )
	{
		_transaction->begin();
	}
	return b;
}


bool CConnection::commit(bool cashed)
{
	bool b = _connImpl->commit();
	if( cashed && _transaction->isBegin() )
	{
		return _transaction->commit();
	}
	return b;
}


bool CConnection::rollback(bool cashed)
{
	bool b = _connImpl->rollback();
	if( cashed && _transaction->isBegin() )
	{
		return _transaction->rollback();
	}
	return b;
}

bool CConnection::connect()
{
	return _connImpl->connect();
}
bool CConnection::reconnect()
{
	return _connImpl->reconnect();
}
void CConnection::close()
{
	_connImpl->close();
}

 
bool CConnection::isClosed()
{
	return _connImpl->isClosed();
}
    
std::auto_ptr< CCallableStatement > CConnection::prepareCall( const char* sql )
{
	return _connImpl->prepareCall( sql );
}
  
void CConnection::setTransactionIsolation( int level )
{
	_connImpl->setTransactionIsolation( level );
}

bool CConnection::keepActive()
{
	return _connImpl->keepActive();
}

std::auto_ptr<CConnection> CConnection::clone()
{
	CConnection *conn = new CConnection( _connImpl->clone() );
	std::auto_ptr<CConnection> autoConn(conn);
	return autoConn;
}

bool CConnection::setEncoding( const char * encode )
{
	return _connImpl->setEncoding( encode );
}

int CConnection::getErrNo() const
{
	return _connImpl->getErrNo();
}

const char * CConnection::getError() const
{
	return _connImpl->getError();
}

cdf::CTransaction* CConnection::getTransaction()
{
	return _transaction;
}

/**
* 设置连接
*/
void CConnection::setConnctionImpl( CConnectionImpl *pConnImpl )
{
	_connImpl = pConnImpl;
}
/**
* 得到连接
*/
CConnectionImpl* CConnection::getConnctionImpl()
{
	return _connImpl;
}
