#include "mysqlconnection.h"
#include <vector>
#include "..\DAOBASE\sqlexception.h"
#include "mysqlstatement.h"
#include "..\DAOBASE\connectionmanager.h"

#ifdef DAF_USED_MYSQL

using namespace DAFrame;
using namespace DAFrame::mysql;


#define VALIDCONN if ( NULL == _conn || ! _connected ) \
					throw CSQLException(ERROR_DATABASE_INVALIDOPER,\
					"Odbc Connection Not Connected");

char CMySQLConnection::_defultEncoding[32] = "utf8";

CMySQLConnection::CMySQLConnection()
	:_host(""),_port(3306),_database(""),_userName(""),_passWord("")
	,_conn(NULL),_connected(false),_autoCommit(true),_begin(false),_stmt(NULL)
{
	_encoding = _defultEncoding;
}

CMySQLConnection::CMySQLConnection(const std::string& host,
								   unsigned short port
								   ,const std::string& dataBase,
								   const std::string& userName,
								   const std::string& password,
								   const std::string& encoding
								   )
								: _host(host),_port(port),_database(dataBase),
								  _userName(userName),_passWord(password),_conn(NULL),
								  _connected(false),_autoCommit(true),_encoding(encoding),
								  _begin(false),
								  _stmt(NULL)
{
}

CMySQLConnection::~CMySQLConnection()
{
	close();
}

DAFrame::CConnectionImpl* CMySQLConnection::clone()
{
	if ((this->_userName=="")||(this->_host==""))
	{
		throw CSQLException(ERROR_DATABASE_INVALIDPROTOCOL,
			"Connection param error while calling CConnectionImpl::clone"
			);
	}

	return new CMySQLConnection(
		_host.c_str(),
		_port,
		_database.c_str(),
		_userName.c_str(),
		_passWord.c_str(),
		_encoding
		);
}

void CMySQLConnection::close()
{
	if( _stmt != NULL )
	{
		_stmt->closeConn();
		_stmt = NULL;
	}
	if ( _conn != NULL )
	{
		mysql_close(_conn);
		_conn = NULL;
	}
	_connected = false;
}

bool CMySQLConnection::keepActive()
{
	if ( _conn != NULL )
	{
		if( 0 == mysql_ping(_conn) )
			return true;
	}
	return false;
}

bool CMySQLConnection::commit()
{
	VALIDCONN;
	if( _begin )
	{
		_begin = false;
		return ( 0 == mysql_commit(_conn) );
	}
	return false;
}

bool CMySQLConnection::rollback()
{
	VALIDCONN;
	if( _begin )
	{
		_begin = false;
		return ( 0 == mysql_rollback(_conn) );
	}
	return true;
}

bool CMySQLConnection::connect()
{
	close();
	_conn = mysql_init(NULL);
	if ( NULL == _conn )
	{
		throw CSQLException(ERROR_DATABASE_INVALIDOPER,
			"mysql_init return null"
			);
	}
	_connected = ( NULL != mysql_real_connect(_conn,_host.c_str(),_userName.c_str(),
							_passWord.c_str(),_database.c_str(),_port,NULL,0) );
	if( !_connected )
	{
		close();
		throw CSQLException(ERROR_DATABASE_INVALIDOPER,
			"mysql_real_connect error");
	}
	this->setAutoCommit(_autoCommit);
	setEncoding(_encoding.c_str());
	return _connected;
}
bool CMySQLConnection::reconnect()
{
	return connect();
}
bool CMySQLConnection::isClosed()
{
	if ( 0 == mysql_ping(_conn) )
		return true;
	close();
	return false;
}

void CMySQLConnection::setAutoCommit(bool autoCommit)
{
	VALIDCONN;
	mysql_autocommit(_conn,autoCommit);
	_autoCommit = autoCommit;
}

bool CMySQLConnection::getAutoCommit()
{
	VALIDCONN;
	return _autoCommit;
}

void CMySQLConnection::setTransactionIsolation(int level)
{
	throw CSQLException(ERROR_DATABASE_UNSUPPORT,"Not Support");
}

bool CMySQLConnection::begin()
{
	VALIDCONN;
	if( !_begin )
	{
		_begin = true;
		return ( 0 == mysql_real_query(_conn,"begin",sizeof("begin")) );
	}
	return false;
}

int CMySQLConnection::getErrNo() const
{
	VALIDCONN;
	return mysql_errno(_conn);
}

const char* CMySQLConnection::getError() const
{
	VALIDCONN;
	return mysql_error(_conn);
}

std::auto_ptr<DAFrame::CStatement> CMySQLConnection::createStatement()
{
	std::auto_ptr<CMySQLStatement> stmt(new CMySQLStatement(*this));
	if( _stmt )
	{
		_stmt->close();
		_stmt = NULL;
	}
	_stmt = stmt.get();
	return std::auto_ptr<CStatement>( stmt.release() );
}

std::auto_ptr<DAFrame::CStatement> CMySQLConnection::prepareStatement(const char* sql)
{
	std::auto_ptr<CMySQLStatement> stmt(new CMySQLStatement(*this));
	if( _stmt )
	{
		_stmt->close();
		_stmt = NULL;
	}
	_stmt = stmt.get();
	stmt->prepare(sql);
	return std::auto_ptr<DAFrame::CStatement>(stmt.release());
}

std::auto_ptr<CCallableStatement> CMySQLConnection::prepareCall(const char* sql)
{
	throw CSQLException(ERROR_DATABASE_UNSUPPORT,"Not Support");
	//return NULL;
}

bool CMySQLConnection::setEncoding(const char * encode/* = "gb2312"*/)
{
	if( _conn && encode && (*encode))
	{
		if( -1 == mysql_set_character_set(_conn, encode) )
		{
			ThrowSQLException<CSQLException>(ERROR_DATABASE_UNSUPPORT ,
				"CMySQLConnection::setEncoding Error code:%d dis:%s" ,
				getErrNo() , getError() );
		};
	}
	else
	{
		if( encode && (*encode) )
		{
			_encoding = encode;
		}
	}
	return true;
}

bool CMySQLConnection::setConnectString(const char * connString , 
										const char * userName , 
										const char * userPwd)
{
	std::vector<std::string> params;
	DAFrame::CConnectionManager::parseProtocol(params, connString);
	if ( params.size() < 2 )
		throw CSQLException(ERROR_DATABASE_INVALIDPROTOCOL,"Unknow Protocol");
	std::vector<std::string>::iterator iparam = params.begin();
	if ( strcmp((*iparam++).c_str(),"mysql") != 0 )
		throw CSQLException(ERROR_DATABASE_INVALIDPROTOCOL,"Unknow Protocol");
	std::string host = (*iparam++);
	std::string database;
	short port = 0;

	if ( iparam != params.end() )
		port = atoi((*iparam++).c_str());
	if ( iparam != params.end() )
		database = (*iparam);
	_host = host;
	_port = port;
	_database = database;
	_userName = userName;
	_passWord = userPwd;
	return true;
}

void CMySQLConnection::clearStmt( CMySQLStatement* stmt )
{
	if( _stmt == stmt )
	{
		_stmt = NULL;
	}
}

void CMySQLConnection::initialize(const char * encoding,const bool regist)
{
	strncpy( _defultEncoding , encoding , sizeof( _defultEncoding ) - 1 );
	if( regist )
	{
		CConnectionManager::registProtocol("mysql",new CMySQLConnection);
	}
}
void CMySQLConnection::finalize()
{
	CConnectionManager::unregistProtocol("mysql");
}

#endif