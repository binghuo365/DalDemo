#ifndef _CMYSQLSTATEMENT_H_
#define _CMYSQLSTATEMENT_H_
#include "../DAOBASE/publicdef.h"

#ifdef DAF_USED_MYSQL

namespace DAFrame
{
	namespace mysql
	{
		class CMySQLConnection;
		class CMySQLResultSet;

		class CMySQLStatement : public CStatement
		{
		protected:
			friend class CMySQLResultSet;
			CMySQLConnection* _conn;
			CMySQLResultSet* _lastRs;
			std::string _sql;
			MYSQL_STMT* _stmt;
			MYSQL_BIND* _params;
			
			int _paramCount;
			
		protected:
			void prepareParams();
			
			void validIndex(int index );
			
			void destroyParams();
			
			void clearParam(int index );
			
			void cleanParam(MYSQL_BIND& param);
			
		public:
			
			CMySQLStatement( ::DAFrame::mysql::CMySQLConnection& conn);
			
			~CMySQLStatement();
			
			long64_t getLastInsertID();
			
			void close();

			void closeConn();

			void clearResultSet( CMySQLResultSet* rs );
			
			long64_t getInsertID( const void* pParam);
			
			std::auto_ptr<CResultSet> executeQuery(const char* pSQL);
			
			int executeUpdate(const char* pSQL);
			
			bool execute(const char* pSQL);
			
			bool execute();
			
			std::auto_ptr<CResultSet> executeQuery();
			
			int executeUpdate();
			
			void clearParameters();
			
			void setByte(int index , char val );
			
			void setBytes(int index, const char* val, int length );
			
			void setBoolean(int index, bool val);
			
			void setString(int index, const std::string& val);
			
			void setInt(int index, int val);
			
			void setDouble(int index, double val);
			
			void setNull(int index, EDATATYPE dateType );
			
			void setDate(int index, const CDateTime& value );
			
			void setTime(int index, const CDateTime& value );
			
			void setTimestamp(int index, const CDateTime& value );
			
			void setLong64(int index, long64_t Value); 	 
			
			void prepare(const char* pSql);
			
			int getErrNo();
			
			const char* getError();
		};
	}
}

#endif

#endif
