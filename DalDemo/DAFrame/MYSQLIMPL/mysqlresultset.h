#ifndef _DFA_DB_MYSQLRESULTSET_H_
#define _DFA_DB_MYSQLRESULTSET_H_
#include <Winsock2.h>
#include "../DAOBASE/publicdef.h"
#include "../DAOBASE/resultset.h"
#include <map>

#ifdef DAF_USED_MYSQL

#include <mysql.h>

namespace DAFrame
{
	namespace mysql
	{
		class CMySQLStatement;
		class CMySQLCallableStatement;
		class CMySQLConnection;
		
		class CMySQLResultSet : public CResultSet
		{
		protected :
			MYSQL_RES* _metaData;
			CMySQLStatement* _stmt;
			DAFrame::mysql::CResultData* _resultData;
			MYSQL_BIND* _result;
			int _fieldCount;
			std::map<std::string,int> _fields;
			
		protected :
			void validIndex(int index);
			
			void cleanParam(MYSQL_BIND& pBind);
		public:
			CMySQLResultSet(CMySQLStatement& Stmt);
			~CMySQLResultSet();
			void clear();
			bool init();
			void close();
			
			int getColumnCount();
			
			EDATATYPE getColumnDataType(int index);
			
			std::string getColumnName(int index);
			
			bool next();
			
			int findColumn(
				const char* column
				);
			
			char getByte(
				int index,
				bool bNullThrow = true,
				char Default = 0
				);
			
			char getByte(
				const char* column,
				bool bNullThrow = true,
				char Default = 0
				);
			
			bool getBytes(
				int index, 
				char* pOutBuffer, 
				int& nLength,
				bool bNullThrow = true,
				const char* pDefault = DEFAULT_STRING
				);
			
			bool getBytes(
				const char* column,
				char* pOutBuffer, 
				int& nLength,
				bool bNullThrow = true,
				const char* pDefault = DEFAULT_STRING
				);
			
			virtual bool getBoolean(
				int index ,
				bool nullThrow = true ,
				bool defaultValue = false 
				);
			
			virtual bool getBoolean(
				const char* column ,
				bool nullThrow = true ,
				bool defaultValue = false 
				);
			
			std::string getString(
				int index,
				bool bNullThrow = true,
				const char* pDefault = DEFAULT_STRING
				);
			
			std::string getString(
				const char* pColumn,
				bool bNullThrow = true,
				const char* pDefault = DEFAULT_STRING
				);
			
			int getInt(
				int index,
				bool bNulLThrow = true,
				int nDefault= DEFAULT_INT
				);
			
			int getInt(
				const char* pColumn,
				bool bNulLThrow = true,
				int nDefault= DEFAULT_INT
				);
			
			double getDouble(
				int index,
				bool bNulLThrow = true,
				double dDefault= DEFAULT_DOUBLE
				);
			
			double getDouble(
				const char* pColumn,
				bool bNulLThrow = true,
				double dDefault= DEFAULT_DOUBLE
				);
			
			bool isNull(int index);
			
			bool isNull(const char* pColumn);
			
			CDateTime getDate(
				int index,
				bool bNullThrow = true,
				const CDateTime& Default = DEFAULT_DATETIME
				);
			
			CDateTime getDate(
				const char* pColumn,
				bool bNullThrow = true,
				const CDateTime& Default = DEFAULT_DATETIME
				);
			
			CDateTime getTime(
				int index,
				bool bNullThrow = true,
				const CDateTime& Default = DEFAULT_DATETIME
				);
			
			CDateTime getTime(
				const char* pColumn,
				bool bNullThrow = true,
				const CDateTime& Default = DEFAULT_DATETIME
				);
			
			CDateTime getTimestamp(
				int index,
				bool bNullThrow = true,
				const CDateTime& Default = DEFAULT_DATETIME
				);
			
			CDateTime getTimestamp(
				const char* pColumn,
				bool bNullThrow = true,
				const CDateTime& Default = DEFAULT_DATETIME
				);
			
			long64_t getLong64(
				int index,
				bool bNullThrow = true,
				long64_t nDefault = DEFAULT_LONG64 
				);
			
			long64_t getLong64(
				const char* pParamName,
				bool bNullThrow = true,
				long64_t nDefault = DEFAULT_LONG64 
				);
		};
	}
}

#endif

#endif
