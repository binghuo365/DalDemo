#ifndef _DAFRAME_PUBLIC_DEF_H_
#define _DAFRAME_PUBLIC_DEF_H_

class CResultSet;
class CConnectionImpl;
class CConnection;
class CStatement;

typedef unsigned __int64 ulong64_t;
typedef long long  long64_t;

namespace DAFrame
{
	enum EDATATYPE
	{
		TYPE_INT,
		TYPE_STRING,
		TYPE_DATE,
		TYPE_TIME,
		TYPE_TIMESTAMP,
		TYPE_LONG64,
		TYPE_DOUBLE,
		TYPE_CHAR,
		TYPE_BLOB,
	};
	enum DATABSE_ERROR
	{
		ERROR_DATABASE_INVALIDOPER = 10001,
		ERROR_DATABASE_UNSUPPORT = 10002,
		ERROR_DATABASE_INVALIDPROTOCOL = 10003,
		ERROR_DATABASE_INVALIDDATATYPE = 10004,
		ERROR_DATABASE_INDEXOUT = 10005,
		ERROR_DATABASE_CLOSED = 10006,
		ERROR_DATABASE_COMMON = 10007,
		ERROR_DATABASE_NULLVALUE = 10008,
		ERROR_INIT_RESOURCES = 10009,
		ERROR_CONNECT_FAILURE = 10010,
		ERROR_NOT_HAVE_COLUMN = 10011,
		ERROR_NOT_DATA_TYPE = 10012,
	};

#define DEFAULT_LONG64		0
#define DEFAULT_DATETIME	CDateTime()
#define DEFAULT_STRING		""
#define DEFAULT_INT			0
#define DEFAULT_DOUBLE		0

#ifdef _ORACLE_
#define _SYSDATE_ "sysdate"
#elif defined(_MYSQL_)
#define _SYSDATE_ "sysdate()"
#elif defined(_SQLSERVER_)
#define _SYSDATE_ "getdate()"
#else
#define _SYSDATE_ "sysdate()"
#endif

#ifdef _ORACLE_
#define CDF_BINARY_CMP ""
#elif defined(_MYSQL_)
#define CDF_BINARY_CMP "binary"
#elif defined(_SQLSERVER_)
#define CDF_BINARY_CMP ""
#else
#define CDF_BINARY_CMP ""
#endif

#define DAF_USED_MYSQL
}


#endif