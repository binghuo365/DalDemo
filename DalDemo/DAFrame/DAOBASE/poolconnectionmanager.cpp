#include "poolconnectionmanager.h"
#include "connectionpool.h"
#include "sqlexception.h"

using namespace DAFrame;

std::auto_ptr<CConnectionPool> CPoolConnectionManager::_connPool;

CPoolConnAutoPtr<CPoolConnection> CPoolConnectionManager::getConnection()
{
	if( _connPool.get() == NULL )
	{
		ThrowSQLException<CSQLException>( ERROR_DATABASE_INVALIDOPER ,
			"CPoolConnectionManager::getConnection null pool");
	}
	return _connPool->getConnection();
}

void CPoolConnectionManager::initialize(
										const char* url , 
										int count , 
										const char * user ,
										const char * pwd )
{
	if( _connPool.get() == NULL )
	{
		if( _connPool.get() == NULL )
		{
			_connPool = std::auto_ptr<CConnectionPool>(
				new CConnectionPool( 
				url ,
				count ,
				user ,
				pwd
				)
				);
		}
	}
}

void CPoolConnectionManager::finalize()
{
	_connPool = std::auto_ptr<CConnectionPool>(NULL);
}
