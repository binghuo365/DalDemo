#include "publicdef.h"
#include "sqlexception.h"
#include "poolconnection.h"
#include "connectionimpl.h"
#include "connectionpool.h"

using namespace DAFrame;
//
CPoolConnection::CPoolConnection( 
								DAFrame::CConnectionImpl * connImpl,
								 CConnectionPool* connectionPool
								 )
:CConnection(connImpl),_connectionPool(connectionPool),_isIdle(true),_cached(true)
{
}

void CPoolConnection::putConnection()
{
	if (!this->_isIdle)
	{
		_connImpl->rollback();
		if( getTransaction()->isBegin() )
		{
			getTransaction()->rollback();
		}
		else
		{
			if( _cached )
			{
				getTransaction()->commit();
			}
		}
		_cached = true;
		this->_connectionPool->putConnection(this);	
	}	
}

void CPoolConnection::close()
{
	
}

CPoolConnection::~CPoolConnection()
{
	if ( _connImpl != NULL )
	{
		delete this->_connImpl;
		_connImpl = NULL;
	}
}

bool CPoolConnection::isClosed()
{
	if (!this->_isIdle)
	{
		return this->_connImpl->isClosed();
	}
	else
	{
		return true;
	}
}

std::auto_ptr<DAFrame::CConnection> CPoolConnection::clone()
{
	throw CSQLException(ERROR_DATABASE_UNSUPPORT,"CPoolConnection::clone is not supported");
}
