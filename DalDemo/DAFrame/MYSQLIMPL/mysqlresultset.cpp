#include "../DAOBASE/publicdef.h"

#ifdef DAF_USED_MYSQL

#include "mysqlpublic.h"
#include "mysqlmetadata.h"
#include "mysqlresultset.h"

using namespace DAFrame;
using namespace DAFrame::mysql;

#ifdef DAF_WIN32
long64_t atol64(const char * val)
{
	return _atoi64(val);
}
#endif

#ifdef CDE_LINUX
#include <ctype.h>
#define _strdup(a) strdup(a)
#endif

std::string to_lower( const char * p )
{
	std::string str(p);
	for( char * buf = (char*)str.c_str() ; *p != '\0'  ; buf ++ )
	{
		if( *buf >= 'A'&& *buf <= 'Z' )
		{
			*buf = *buf + 0x20;
		}
	}
	return str;
}

#define THROWEXCEPTION throw CSQLException(_stmt->getErrNo(),_stmt->getError());

#define EXECUTE(a) if ( 0 != a ) \
			THROWEXCEPTION;

#define VALIDROW if ( _row == NULL ) \
		throw CSQLException(ERROR_DATABASE_INVALIDOPER,"Row Not Exist");


#define CHECKTYPE(a) 	if ( _resultData[index-1]._dataType != a ) \
		ThrowSQLException<CSQLException>(ERROR_DATABASE_INVALIDDATATYPE,\
		"%s[%d] Invalid Data Type",getColumnName(index).c_str(),index);

#define NULLVALUEEXCEPTOIN ThrowSQLException<CSQLException>(ERROR_DATABASE_NULLVALUE,\
	"%s[%d]NULL VALUE",getColumnName(index).c_str(),index)

#define RSCHECKNULL(nullThrow,DEFAULT) { \
			if ( nullThrow ) \
				NULLVALUEEXCEPTOIN; \
			else \
				return DEFAULT; \
		}


#define CHECKNULL(NULLTHROW,DEFAULT)	\
	if ( _row[index-1] == NULL ) RSCHECKNULL(NULLTHROW,DEFAULT);
/*

		Class	CMySQLResultSet

*/

CMySQLResultSet::CMySQLResultSet(CMySQLStatement& stmt)
{
	_stmt = &stmt;
	_metaData = NULL;
	_resultData = NULL;
	_fieldCount = 0;
}

CMySQLResultSet::~CMySQLResultSet()
{
	clear();
}

bool CMySQLResultSet::init()
{
	_metaData = mysql_stmt_result_metadata(_stmt->_stmt);
	if ( _metaData == NULL )
		THROWEXCEPTION;
	_fieldCount = mysql_num_fields(_metaData);
	this->_fields.clear();
	if ( _fieldCount > 0 )
	{
		_resultData = new CResultData[_fieldCount];
		_result = new MYSQL_BIND[_fieldCount];
		MYSQL_FIELD* fields = mysql_fetch_fields(_metaData);
		for ( int i = 0 ; i < _fieldCount ; i ++ )
		{
			MYSQL_FIELD* field = &fields[i];
			CResultData* pData = &_resultData[i];
			pData->_columnName = field->name;
			_fields[pData->_columnName] = i+1;
			MYSQL_BIND* bind = &_result[i];
			memset(bind,0,sizeof(MYSQL_BIND));
			bind->buffer_type = field->type;
			bind->is_null = new char;
			bind->length = new unsigned long;
			EDATATYPE type = getDataType(field->type);
			switch ( type )
			{
				case TYPE_INT :
					bind->buffer = ::malloc(sizeof(int));
					break;
				case TYPE_LONG64 :
					bind->buffer = ::malloc(sizeof(long64_t));
					break;
				case TYPE_DOUBLE :
					bind->buffer = ::malloc(sizeof(double));
					break;
				case TYPE_DATE :
					bind->buffer = ::malloc(sizeof(MYSQL_TIME));
					break;
				case TYPE_TIME :
					bind->buffer = ::malloc(sizeof(MYSQL_TIME));
					break;
				case TYPE_TIMESTAMP :
					bind->buffer = ::malloc(sizeof(MYSQL_TIME));
					break;
				case TYPE_STRING :
					bind->buffer = ::malloc(field->length);
					*bind->length = field->length;
					bind->buffer_length = field->length;
					break;
				case TYPE_BLOB:
					bind->buffer = ::malloc(field->length);
					*bind->length = field->length;
					bind->buffer_length = field->length;
					break;
			}
			pData->_dataType = type;
		}
		EXECUTE(mysql_stmt_bind_result(_stmt->_stmt,_result));
	}
	return true;
}

bool CMySQLResultSet::next()
{
	int retval = mysql_stmt_fetch(_stmt->_stmt);
	if ( retval == 1 )
	{
		throw CSQLException(_stmt->getErrNo(),_stmt->getError());
	}
	if ( retval == MYSQL_NO_DATA )
	{
		//close();
		return false;
	}
	return true;
}

void CMySQLResultSet::cleanParam(MYSQL_BIND& bind)
{
	if ( bind.is_null != NULL )
	{
		delete bind.is_null;
		bind.is_null = NULL;
	}
	if ( bind.length != NULL )
	{
		delete bind.length;
		bind.length = NULL;
	}
	if ( bind.buffer != NULL )
	{
		free(bind.buffer);
		bind.buffer = NULL;
	}
}

void CMySQLResultSet::clear()
{
	if ( _metaData != NULL )
	{
		mysql_free_result(_metaData);
		_metaData = NULL;
	}
	if ( _resultData != NULL )
	{
		delete[] _resultData;
		_resultData = NULL;
	}
	if ( _result != NULL )
	{
		for ( int i = 0 ; i < _fieldCount ; i ++ )
		{
			cleanParam(_result[i]);
		}
		delete[] _result;
		_result = NULL;
	}
	if( _stmt != NULL )
	{
		_stmt->clearResultSet( this );
		_stmt = NULL;
	}
}

void CMySQLResultSet::close()
{
	clear();
	if ( _stmt != NULL )
	{
		_stmt->close();
		_stmt = NULL;
	}
}

int CMySQLResultSet::findColumn(const char* columnName)
{
	std::map<std::string,int>::iterator iter = _fields.find(columnName);
	if ( iter == _fields.end() )
	{
		return -1;
	}
	return iter->second;
}

std::string CMySQLResultSet::getColumnName(int index)
{
	validIndex(index);
	return _resultData[index-1]._columnName;
}

void CMySQLResultSet::validIndex(int index)
{
	if ( index <= 0 || index > this->_fieldCount )
		throw CSQLException(ERROR_DATABASE_INDEXOUT,"Index Out of Bounds");
}

int CMySQLResultSet::getColumnCount()
{
	return _fieldCount;
}

EDATATYPE CMySQLResultSet::getColumnDataType(int index)
{
	validIndex(index);
	return _resultData[index-1]._dataType;
}

//*****************get funcs***********************

bool CMySQLResultSet::getBoolean(const char* column ,
										bool nullThrow ,
										bool defaultValue )
{
	return getBoolean(this->findColumn(column));
}

bool CMySQLResultSet::getBoolean(
										int index ,
										bool nullThrow ,
										bool defaultValue
										)
{
	validIndex(index);
	bool retval = false;
	MYSQL_BIND* bind = &_result[index-1];
	if ( bind->buffer_type != MYSQL_TYPE_TINY )
		throw CSQLException(0x03,"Invalid Data Type");
	return *(char*)bind->buffer;
	return retval;
}


#define RSCHECKTYPE(a) if ( bind->buffer_type != a ) \
		throw CSQLException(ERROR_DATABASE_INVALIDDATATYPE,"Invalid Data Type");

#define PRSCHECKNULL(bThrow,DEFAULT) if ( *bind->is_null ) RSCHECKNULL(nullThrow,DEFAULT);

char CMySQLResultSet::getByte(const char* columnName,bool nullThrow,char Default)
{
	return getByte(findColumn(columnName),nullThrow,Default);
}

char CMySQLResultSet::getByte(int index,bool nullThrow,char Default)
{
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_TINY);
	PRSCHECKNULL(nullThrow,Default);
	return *(char*)bind->buffer;
}

bool CMySQLResultSet::getBytes(const char* columnName,char* pOutBuffer,int& nLength,bool nullThrow,const char* pDefault)
{
	return getBytes(findColumn(columnName),pOutBuffer,nLength,nullThrow,pDefault);
}

bool CMySQLResultSet::getBytes(int index,char* pOutBuffer,int& nLength,bool nullThrow,const char* pDefault)
{
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_BLOB);
	const char* pvalue = NULL;
	size_t size = 0;
	if ( *bind->is_null )
	{
		if ( nullThrow || pDefault == NULL )
		{
			throw CSQLException(ERROR_DATABASE_NULLVALUE,"NULL VALUE");
		}
		pvalue = pDefault;
		size = strlen(pDefault);
	}
	else
	{
		size = nLength;
		if ( size > bind->buffer_length )
			size = bind->buffer_length;
	}
	memcpy(pOutBuffer,pvalue,size);
	nLength = (int)size;
	return true;
}

CDateTime CMySQLResultSet::getDate(const char* column,bool nullThrow,const CDateTime& Default)
{
	return getDate(findColumn(column),nullThrow,Default);
}

CDateTime CMySQLResultSet::getDate(int index,bool nullThrow,const CDateTime& Default)
{
	CDateTime time;
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_DATETIME);
	PRSCHECKNULL(nullThrow,Default);
	convert(time,(*(MYSQL_TIME*)bind->buffer));
	return time;
}

CDateTime CMySQLResultSet::getTime(const char* column,bool nullThrow,const CDateTime& Default)
{
	return getTime(findColumn(column),nullThrow,Default);
}

CDateTime CMySQLResultSet::getTime(int index,bool nullThrow,const CDateTime& Default)
{
	CDateTime time;
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_TIME);
	PRSCHECKNULL(nullThrow,Default);
	convert(time,(*(MYSQL_TIME*)bind->buffer));
	return time;
}

CDateTime CMySQLResultSet::getTimestamp(const char* column,bool nullThrow,const CDateTime& Default)
{
	return getTimestamp(findColumn(column),nullThrow,Default);
}

CDateTime CMySQLResultSet::getTimestamp(int index,bool nullThrow,const CDateTime& Default)
{
	CDateTime time;
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_TIMESTAMP);
	PRSCHECKNULL(nullThrow,Default);
	convert(time,(*(MYSQL_TIME*)bind->buffer));
	return time;
}

bool CMySQLResultSet::isNull(const char* column)
{
	return isNull(findColumn(column));
}

bool CMySQLResultSet::isNull(int index)
{
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	return 0 != *bind->is_null;
}

std::string CMySQLResultSet::getString(const char* column,bool nullThrow,const char* pDefault)
{
	return getString(findColumn(column),nullThrow,pDefault);
}

std::string CMySQLResultSet::getString(int index,bool nullThrow,const char* pDefault)
{
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	if ( bind->buffer_type != MYSQL_TYPE_STRING && bind->buffer_type != MYSQL_TYPE_VAR_STRING )
		throw CSQLException(ERROR_DATABASE_INVALIDDATATYPE,"Invalid Data Type");
	PRSCHECKNULL(nullThrow,pDefault);
	return (char*)bind->buffer;
}

long64_t CMySQLResultSet::getLong64(const char* column,bool nullThrow,long64_t nDefault)
{
	return getLong64(findColumn(column),nullThrow,nDefault);
}

long64_t CMySQLResultSet::getLong64(int index,bool nullThrow,long64_t nDefault)
{
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_LONGLONG);
	PRSCHECKNULL(nullThrow,nDefault);
	return *(my_ulonglong*)(bind->buffer);
}

double CMySQLResultSet::getDouble(const char* column,bool nullThrow,double defaultV )
{
	return getDouble(findColumn(column),nullThrow,defaultV);
}

double CMySQLResultSet::getDouble(int index,bool nullThrow,double defaultV)
{
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_DOUBLE);
	PRSCHECKNULL(nullThrow,defaultV);
	return *(double*)(bind->buffer);
}

int CMySQLResultSet::getInt(const char* column,bool nullThrow,int defaultV)
{
	return getInt(findColumn(column),nullThrow,defaultV);
}

int CMySQLResultSet::getInt(int index,bool nullThrow,int defaultV)
{
	validIndex(index);
	MYSQL_BIND* bind = &_result[index-1];
	RSCHECKTYPE(MYSQL_TYPE_LONG);
	PRSCHECKNULL(nullThrow,defaultV);
	return *(long*)(bind->buffer);
}

#endif
