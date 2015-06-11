#include "connectionpool.h"
#include "poolconnection.h"
#include "sqlexception.h"
#include "connectionmanager.h"
#include "poolconnautoptr.h"

using namespace DAFrame;

CConnectionPool::CConnectionPool(
								 const char* url ,
								 int maxConnections,
								 const char* user ,
								 const char* pwd ,
								 int minConnections
								 )
:_maxConnections(maxConnections),_connectionCount(0),
_lastUserIndex(0),_minConnections(minConnections),_idleConnectionCount(0),
_url(url),_user(user),_userPwd(pwd)
{
	_connections.resize( maxConnections );
	for ( unsigned short i = 0 ; i < maxConnections ; i ++ )
	{
		_connections[i] = NULL;
	}
	_maxConnections = maxConnections;
	if( _minConnections > _maxConnections )
	{
		_minConnections = _maxConnections;
	}
	_connectionCount = 0;
	_idleConnectionCount = 0;
}

//
CConnectionPool::~CConnectionPool()
{
	for ( unsigned short i = 0 ; i < this->_maxConnections; i ++ )
	{
		try
		{
			if ( NULL != _connections[i]  )
				delete _connections[i];
		}
		catch(...)
		{
		}
	}

	_connections.clear();
}

//
void CConnectionPool::putConnection( CPoolConnection* conn )
{
	if ( ( conn->_connectionPool == this ) && ( conn->_isIdle==false ) )
	{
		conn->_isIdle = true;
		_idleConnectionCount ++;
	}
}

CPoolConnection* CConnectionPool::getIdleConnection()
{
	CPoolConnection* poolConn = NULL;
	if ( _idleConnectionCount > 0 )
	{
		unsigned short i;
		for ( i = _lastUserIndex ; i <_connectionCount ; i ++ )
		{
			poolConn = _connections[i];
			if ( (poolConn==NULL) || ( !poolConn->_isIdle ) )
			{
				continue;
			}
			poolConn->_isIdle = false;
			_idleConnectionCount--;
			_lastUserIndex = i;
			return poolConn;
		}
		for ( i = 0 ; i < _lastUserIndex ; i ++ )
		{
			poolConn = _connections[i];
			if ( (poolConn==NULL) || ( !poolConn->_isIdle ) )
			{
				continue;
			}
			poolConn->_isIdle = false;
			_idleConnectionCount--;
			_lastUserIndex = i;
			return poolConn;
		}
	}
	return poolConn;
}

CPoolConnAutoPtr<DAFrame::CPoolConnection>
DAFrame::CConnectionPool::getConnection(const long waitMill)
{
	CPoolConnection* poolConn = NULL;
	{
		if( 0 == _connectionCount )
		{
			for( int i = 0 ; i < _minConnections ; i ++ )
			{
				try
				{
					std::auto_ptr<CConnection> ptr =
						CConnectionManager::getConnection(
						this->_url.c_str(),
						this->_user.c_str(),
						this->_userPwd.c_str()
						);
					CConnectionImpl* pConn= ptr->getConnctionImpl();
					ptr->setConnctionImpl(NULL);
					poolConn = new CPoolConnection(pConn,this);
					_connections[_connectionCount] = poolConn;
					_connectionCount ++;
					_idleConnectionCount ++;
				}
				catch (CSQLException& e)
				{
					std::string errmsg = e.what();
					errmsg = "Init CConnectionPool error! " + errmsg;
					throw CSQLException(-3,errmsg.c_str());
				}
			}
		}
		poolConn = (CPoolConnection*)getIdleConnection();

		if( NULL == poolConn)
		{
			if ( this->_connectionCount < this->_maxConnections )
			{
				try
				{
					std::auto_ptr<CConnection> ptr =
						CConnectionManager::getConnection(
						this->_url.c_str(),
						this->_user.c_str(),
						this->_userPwd.c_str()
						);

					CConnectionImpl* pConn= ptr->getConnctionImpl();
					ptr->setConnctionImpl(NULL);
					poolConn = new CPoolConnection(pConn,this);
					poolConn->_isIdle = false;
					_connections[_connectionCount] = poolConn;
					_connectionCount ++;

				}
				catch (CSQLException& e)
				{
					std::string errmsg = e.what();
					errmsg = "getConnection by CConnectionPool error! " + errmsg;
					throw CSQLException(-3,errmsg.c_str());
				}
			}
			else
			{
				throw CSQLException(-4,"getConnection by CConnectionPool error! no connection available!");
			}
		}
	}
	if( !poolConn->keepActive() )
	{
		poolConn->reconnect();
	}
	return CPoolConnAutoPtr<CPoolConnection>( poolConn );
}

void CConnectionPool::keepActive()
{
	if ( _idleConnectionCount > 0 )
	{
		for ( unsigned short i = 0 ; i < this->_connectionCount ; i ++ )
		{
			CPoolConnection* poolConn = _connections[i];
			if (( poolConn == NULL ) || ( !poolConn->_isIdle ))
				continue;
			if( !poolConn->keepActive() )
			{
				poolConn->reconnect();
			};
		}
	}
}
