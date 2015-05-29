#ifndef _DAF_STATEMENT_H_
#define _DAF_STATEMENT_H_
#include <memory>
#include "datetime.h"
#include "connection.h"

namespace DAFrame
{
	class CResultSet;
	class CConnection;
	class CStatement
	{
	public:
		CStatement();

		virtual ~CStatement() {};

		virtual void close() = 0;


		virtual long64_t getInsertID(const  void* param ) = 0;

		virtual std::auto_ptr<CResultSet> executeQuery( const char* sql ) = 0;

		virtual int executeUpdate( const char* sql ) = 0;

		virtual bool execute( const char* sql ) = 0;

		virtual bool execute() = 0;

		virtual void prepare( const char* sql ) = 0;

		virtual std::auto_ptr<CResultSet> executeQuery() = 0;

		virtual int executeUpdate() = 0;

		virtual void clearParameters() = 0;

		virtual void setByte(int paramIndex, char value) = 0;

		virtual void setBytes( int paramIndex, const char* value, int length ) = 0;

		virtual void setBoolean(int paramIndex, bool value ) = 0;

		virtual void setString(int paramIndex, const std::string& value ) = 0;

		virtual void setInt(int paramIndex, int value ) = 0;

		virtual void setDouble(int paramIndex, double value ) = 0;

		virtual void setDate(int paramIndex, const CDateTime& value ) = 0;

		virtual void setTime(int paramIndex, const CDateTime& value ) = 0;

		virtual void setTimestamp(int paramIndex, const CDateTime& value ) = 0;

		virtual void setLong64(int paramIndex, long64_t value ) = 0;

		void setConnection(CConnection* conn );

		CConnection* getConnection();

	private:
		CConnection* _conn;
	};
}


#endif
