#include "mysqlpublic.h"
#ifdef DAF_USED_MYSQL
#include "mysqlstatement.h"

#define THROWEXCEPTION throw CSQLException(getErrNo(),getError());
#define EXECUTE(a) if ( 0 != a ) \
			THROWEXCEPTION;

#define VALIDCONN \
	if ( NULL == _conn ) \
	throw CSQLException(ERROR_DATABASE_INVALIDOPER,"Not Connected");

#define VALIDSTMT \
	if ( NULL == _conn ) \
		throw CSQLException(ERROR_DATABASE_INVALIDOPER,"Not Connected"); \
	if ( NULL == _stmt ) \
			throw CSQLException(ERROR_DATABASE_INVALIDOPER,"Not Prepared");

using namespace DAFrame;
using namespace DAFrame::mysql;

CMySQLStatement::CMySQLStatement( CMySQLConnection& conn )
{
	_conn = &conn;
	_stmt = NULL;
	_params = NULL;
	_paramCount = 0;
	_lastRs = NULL;
}

CMySQLStatement::~CMySQLStatement()
{
	close();
	if( _conn )
	{
		_conn->clearStmt( this );
	}
}

void CMySQLStatement::close()
{
	destroyParams();
	if( _lastRs != NULL )
	{
		_lastRs->clear();
		_lastRs = NULL;
	}
	if ( _stmt != NULL )
	{
		mysql_stmt_close(_stmt);
		_stmt = NULL;
	}
}

void CMySQLStatement::closeConn()
{
	_conn = NULL;
	close();
}

void CMySQLStatement::clearResultSet( CMySQLResultSet* rs )
{
	if( _lastRs == rs )
	{
		_lastRs = NULL;
	}
}

long64_t CMySQLStatement::getLastInsertID()
{
	if ( _stmt != NULL )
		return mysql_stmt_insert_id(_stmt);
	VALIDCONN;
	return mysql_insert_id(_conn->_conn);
}

long64_t CMySQLStatement::getInsertID( const void* pParam)
{
	return getLastInsertID();
}

int CMySQLStatement::executeUpdate(const char* sql)
{
	close();
	VALIDCONN;
	EXECUTE(mysql_real_query(_conn->_conn,sql,(ulong_t)strlen(sql)));
	return (int)mysql_affected_rows(_conn->_conn);
}

bool CMySQLStatement::execute(const char* sql)
{
	close();
	VALIDCONN;
	EXECUTE(mysql_real_query(_conn->_conn,sql,(ulong_t)strlen(sql)));
	return (0 != mysql_affected_rows(_conn->_conn));
}

std::auto_ptr<DAFrame::CResultSet> CMySQLStatement::executeQuery(const char* sql)
{
	prepare( sql );
	return executeQuery();
}

void CMySQLStatement::prepare(const char* sql )
{
	if ( _stmt != NULL )
	{
		close();
	}
	VALIDCONN;
	_stmt = mysql_stmt_init(_conn->_conn);
	if ( _stmt == NULL )
	{
		THROWEXCEPTION;
	}
	EXECUTE(mysql_stmt_prepare( _stmt, sql , (ulong_t)strlen(sql) ) );
	prepareParams();
}

bool CMySQLStatement::execute()
{
	VALIDSTMT;
	EXECUTE(mysql_stmt_bind_param(_stmt,_params));
	EXECUTE(mysql_stmt_execute(_stmt));
	return (0 != mysql_stmt_affected_rows(_stmt));
}

int CMySQLStatement::executeUpdate()
{
	VALIDSTMT;
	EXECUTE(mysql_stmt_bind_param(_stmt,_params));
	EXECUTE(mysql_stmt_execute(_stmt));
	return (int)mysql_stmt_affected_rows(_stmt);
}

std::auto_ptr<DAFrame::CResultSet> CMySQLStatement::executeQuery()
{
	VALIDSTMT;
	EXECUTE(mysql_stmt_bind_param(_stmt,_params));
	EXECUTE(mysql_stmt_execute(_stmt));
	std::auto_ptr<CMySQLResultSet> result(new CMySQLResultSet(*this));
	result->init();
	_lastRs = result.get();
	return (std::auto_ptr<CResultSet>)result;
}

//*************set params*************************
/*
void CMySQLStatement::setBoolean(int index,bool Value)
{
	setByte(index,Value?1:0);
}
*/

void CMySQLStatement::setByte(int index,char Value)
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_TINY;
	bind->buffer = malloc(sizeof(char));
	*((unsigned char*)bind->buffer) = (unsigned char)Value;
	bind->length = 0;
}

void CMySQLStatement::setBytes(int index,const char* Value,int nLength)
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_BLOB;
	bind->buffer_length = nLength;
	bind->buffer = malloc(nLength);
	memcpy(bind->buffer,Value,nLength);
	bind->length = 0;
}

void CMySQLStatement::setDate( int index , const CDateTime& value )
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];
	bind->buffer_type = MYSQL_TYPE_DATETIME;
	bind->buffer = malloc(sizeof(MYSQL_TIME));
	convert(*(MYSQL_TIME*)bind->buffer,value);
	bind->length = 0;
}

void CMySQLStatement::setTime( int index , const CDateTime& value )
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_TIME;
	bind->buffer = malloc(sizeof(MYSQL_TIME));
	convert(*(MYSQL_TIME*)bind->buffer,value);
	((MYSQL_TIME*)bind->buffer)->year = 0;
	((MYSQL_TIME*)bind->buffer)->month = 0;
	((MYSQL_TIME*)bind->buffer)->day = 0;
	bind->length = 0;
}

void CMySQLStatement::setTimestamp( int index , const CDateTime& value )
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_TIMESTAMP;
	bind->buffer = malloc(sizeof(MYSQL_TIME));
	convert(*(MYSQL_TIME*)bind->buffer,value);
	bind->length = 0;
}

void CMySQLStatement::setDouble(int index,double Value)
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_DOUBLE;
	bind->buffer = malloc(sizeof(double));
	*(double*)bind->buffer = Value;
	bind->length = 0;
}

void CMySQLStatement::setInt(int index,int Value)
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_LONG;
	bind->buffer = malloc(sizeof(int));
	*(int*)bind->buffer = Value;
	bind->length = 0;
}

void CMySQLStatement::setLong64(int index,long64_t Value)
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_LONGLONG;
	bind->buffer = malloc(sizeof(long64_t));
	*(long64_t*)bind->buffer = Value;
	bind->length = 0;
}

void CMySQLStatement::setNull(int index,EDATATYPE nEDATATYPE)
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = getDBType(nEDATATYPE);
	bind->is_null = new char;
	*bind->is_null = 1;
	bind->length = 0;
}

void CMySQLStatement::setString(int index,const std::string& Value)
{
	VALIDSTMT;
	validIndex(index);
	MYSQL_BIND* bind = &_params[index-1];//.MYSQL_BIND();
	bind->buffer_type = MYSQL_TYPE_VAR_STRING;
	bind->buffer_length = (ulong_t)Value.length();
	bind->buffer = malloc(Value.length() + 1);
	sprintf((char*)bind->buffer,"%s",Value.c_str());
	bind->length = 0;
}

//*******************CMySQLStatement Funcs***************************
void CMySQLStatement::clearParameters()
{
	destroyParams();
}

//********************other funcs****************
int CMySQLStatement::getErrNo()
{
	if ( _stmt != NULL )
		return mysql_stmt_errno(_stmt);
	return this->_conn->getErrNo();
}

const char* CMySQLStatement::getError()
{
	if ( _stmt != NULL )
		return mysql_stmt_error(_stmt);
	return this->_conn->getError();
}

void CMySQLStatement::prepareParams()
{
	destroyParams();
	_paramCount = mysql_stmt_param_count(_stmt);
	if ( _paramCount > 0 )
	{
		_params = new MYSQL_BIND[_paramCount];
		memset(_params,0,sizeof(MYSQL_BIND)*_paramCount);
	}
}

void CMySQLStatement::destroyParams()
{
	if ( _params != NULL )
	{
		for ( int i = 0 ; i < this->_paramCount ; i ++ )
		{
			cleanParam(_params[i]);
		}
		delete[] _params;
	}
	_paramCount = 0;
	_params = NULL;
}

void CMySQLStatement::cleanParam(MYSQL_BIND& param)
{
	if ( NULL != param.buffer )
	{
		free(param.buffer);
		param.buffer = NULL;
	}
	if ( NULL != param.length )
	{
		delete param.length;
		param.length = NULL;
	}
	if ( NULL != param.is_null )
	{
		delete param.is_null;
		param.is_null = NULL;
	}
}

void CMySQLStatement::clearParam(int index)
{
	//to clear to param
	cleanParam(_params[index - 1]);//.clear();
}

void CMySQLStatement::validIndex(int index)
{
	if ( index > _paramCount || index <= 0 )
	{
		throw CSQLException(ERROR_DATABASE_INDEXOUT,"Index Out Of Bounds");
	}
	clearParam(index);
}

void CMySQLStatement::setBoolean(int index, bool Value)
{
}
#endif
