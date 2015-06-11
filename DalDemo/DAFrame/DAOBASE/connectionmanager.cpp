#include "publicdef.h"
#include "sqlexception.h"
#include "connectionmanager.h"
#include "connectionpool.h"
#include "connection.h"
#include "poolconnautoptr.h"

using namespace DAFrame;

std::auto_ptr< std::map< std::string , DAFrame::CConnectionImpl*> > CConnectionManager::_connPool(NULL);

std::auto_ptr<CConnectionPool> CConnectionManager::getConnectionPool(
																	 const char* pConnectionURL,
																	 int maxConnections,
																	 const char* userName,
																	 const char* userPwd
																	 )
{
	CConnectionPool* conpool = new CConnectionPool(
		pConnectionURL ,
		maxConnections ,
		userName ,
		userPwd
		);

	std::auto_ptr<CConnectionPool> autoptr(conpool);
	return autoptr;
}

std::auto_ptr<DAFrame::CConnection> CConnectionManager::getConnection(
															 const char* connectionURL,
															 const char* userName,
															 const char* userPwd )
{
	std::vector<std::string> params;
	parseProtocol( params , connectionURL );
	if ( params.size() < 2 )
	{
		throw CSQLException(ERROR_DATABASE_INVALIDPROTOCOL,"Unknow Protocol");
	}
	std::vector<std::string>::iterator iter = params.begin();
	std::map<std::string,CConnectionImpl*>::iterator it;
	if( _connPool.get() == NULL )
	{
		throw CSQLException(ERROR_DATABASE_INVALIDPROTOCOL,"UNINIT Protocol");
	}
	it = _connPool->find( (*iter++) );
	if(_connPool->end() == it)
	{
		throw CSQLException(ERROR_DATABASE_INVALIDPROTOCOL,"Unknow Protocol");
	}
	CConnectionImpl *connectionImpl = it->second;
	connectionImpl->setConnectString( connectionURL , userName , userPwd );
	std::auto_ptr<CConnection> conn(new CConnection( connectionImpl->clone() ) );
	if(!conn->connect())
	{
		throw CSQLException( conn->getErrNo() , conn->getError() );
	}
	return conn;
}

void CConnectionManager::finalize()
{
	if( !_connPool.get() )
	{
		return;
	}
	std::map<std::string , CConnectionImpl*>::iterator iter;
	for( iter = _connPool->begin() ; iter != _connPool->end() ; iter++ )
	{
		delete iter->second;
	}
	_connPool->clear();
	_connPool = std::auto_ptr<std::map<std::string , CConnectionImpl*> >(NULL);
}

void CConnectionManager::registProtocol(const char * protocolName, DAFrame::CConnectionImpl * pConnImpl)
{
	if( _connPool.get() == NULL )
	{
		_connPool = std::auto_ptr<std::map<std::string, DAFrame::CConnectionImpl*> >
			(new std::map<std::string, DAFrame::CConnectionImpl*>);
	}
	_connPool->insert( std::make_pair( protocolName , pConnImpl ));
}

void CConnectionManager::unregistProtocol( const char * protocolName )
{
	if( _connPool.get() == NULL )
	{
		_connPool = std::auto_ptr<std::map<std::string , CConnectionImpl*> >
			(new std::map<std::string , CConnectionImpl*>);
	}
	std::map<std::string , CConnectionImpl*>::iterator iter = _connPool->find(  protocolName );
	if( iter != _connPool->end() )
	{
		delete iter->second;
		_connPool->erase( iter );
	}
}

void CConnectionManager::parseProtocol( std::vector<std::string>& params,const char* connectionURL )
{
	const char* p,*begin;;
	begin = p = connectionURL;
	while ( *p )
	{
		if ( ':' == (*p) || '/' == (*p) || '?' == (*p) )
		{
			//
			if ( p - begin > 0 )
			{
				params.push_back(std::string(begin,p-begin));
			}
			begin = p + 1;
		}
		p++;
	}
	if ( p - begin > 1 )
	{
		params.push_back(std::string(begin,p-begin));
	}
}
