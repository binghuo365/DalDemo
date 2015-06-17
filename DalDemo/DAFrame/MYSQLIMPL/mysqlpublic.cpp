#include "mysqlpublic.h"

#ifdef DAF_USED_MYSQL

namespace DAFrame
{
	namespace mysql
	{
		void convert(MYSQL_TIME& SQLTime,const CDateTime& DateTime)
		{
			memset(&SQLTime,0,sizeof(MYSQL_TIME));
			SQLTime.year = DateTime.getYear();
			SQLTime.month = DateTime.getMonth();
			SQLTime.day = DateTime.getDay();
			SQLTime.hour = DateTime.getHour();
			SQLTime.minute = DateTime.getMinute();
			SQLTime.second = DateTime.getSecond();
		}

		void convert(CDateTime& DateTime,const MYSQL_TIME& SQLTime)
		{
			char buffer[40];

			if( SQLTime.year >= 1970 )
			{
				sprintf(buffer,
					"%04d-%02d-%02d %02d:%02d:%02d",
					SQLTime.year,SQLTime.month,SQLTime.day,
					SQLTime.hour,SQLTime.minute,SQLTime.second
					);
			}
			else
			{
				sprintf(buffer,
					"2000-01-01 00:00:00"
					);
			}
			DateTime.parse(buffer,"YYYY-MM-DD hh:mm:ss");
		}

		const int types[][2] = {
			{MYSQL_TYPE_VAR_STRING,TYPE_STRING},
			{MYSQL_TYPE_STRING,TYPE_STRING},
			{MYSQL_TYPE_LONG,TYPE_INT},
			{MYSQL_TYPE_LONGLONG,TYPE_LONG64},
			{MYSQL_TYPE_DOUBLE,TYPE_DOUBLE},
			{MYSQL_TYPE_FLOAT,TYPE_DOUBLE},
			{MYSQL_TYPE_DATE,TYPE_DATE},
			{MYSQL_TYPE_DATETIME,TYPE_DATE},
			{MYSQL_TYPE_TIME,TYPE_TIME},
			{MYSQL_TYPE_TIMESTAMP,TYPE_TIMESTAMP},
			{MYSQL_TYPE_TINY,TYPE_CHAR},
			{MYSQL_TYPE_BLOB,TYPE_BLOB},
		};

		::enum_field_types
			getDBType( EDATATYPE nDataType )
		{
			for ( int i = 0 ; i < sizeof(types) / sizeof(int[2]) ; i ++ )
			{
				if ( types[i][1] == nDataType )
					return (enum_field_types)types[i][0];
			}
			throw CSQLException(ERROR_DATABASE_INVALIDDATATYPE,"DataType Un Supported");
		}

		EDATATYPE getDataType( enum_field_types nSqlType )
		{
			for ( int i = 0 ; i < sizeof(types) / sizeof(int[2]) ; i ++ )
			{
				if ( types[i][0] == nSqlType )
					return (EDATATYPE)types[i][1];
			}
			throw CSQLException(ERROR_DATABASE_INVALIDDATATYPE,"DataType Un Supported");
		}
	}
}

#endif