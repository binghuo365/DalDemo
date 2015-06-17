#ifndef _DFA_DB_MYSQLPUBLIC_H_
#define _DFA_DB_MYSQLPUBLIC_H_
#include <Winsock2.h>
#include "../DAOBASE/publicdef.h"
#ifdef DAF_USED_MYSQL

#include "../DAOBASE/datetime.h"
#include "../DAOBASE/sqlexception.h"
#include <mysql.h>

namespace DAFrame
{
	namespace mysql
	{
		class CMySQLConnection;
		class CMySQLResultSet;
		class CMySQLStatement;
		class CMySQLPrepareResultSet;
		class CMetaData;
		class CResultData;
		
		//mysql date to date
		void convert(MYSQL_TIME& sqlTime ,const CDateTime& dateTime );
		//datatime to mysql date
		void convert(CDateTime& dateTime,const MYSQL_TIME& sqlTime );
		//change type to db type
		enum_field_types getDBType( EDATATYPE dateType );
		//mysql type to system type
		EDATATYPE getDataType(enum_field_types sqlType );
	}
}

#include "mysqlmetadata.h"
#include "mysqlconnection.h"
#include "mysqlresultset.h"
#include "mysqlstatement.h"

#endif

#endif
