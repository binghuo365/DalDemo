#ifndef _DAF_CALLABLE_STATEMENT_H_
#define _DAF_CALLABLE_STATEMENT_H_

#include "publicdef.h"
#include "datetime.h"

namespace DAFrame
{
	class CResultSet;
	class CCallableStatement
	{
	public:
		
		virtual ~CCallableStatement(){};
		
		virtual bool registerResultset(
			int index
			) = 0;
		
		virtual bool execute() = 0;
		
		virtual void close() = 0;
		
		virtual void setByte(
			int paramIndex, 
			char value,
			bool isRegOut=false
			) = 0;
		
		virtual void setBytes(int paramIndex,
			const char* value ,
			int length , 
			bool isRegOut=false) = 0;
		
		virtual void setString(
			int paramIndex,
			const std::string& value,
			bool isRegOut=false
			) = 0;
		
		virtual void setDate(int paramIndex,
			CDateTime value, 
			bool isRegOut=false
			) = 0;
		
		virtual void setDouble(
			int paramIndex, 
			double value, 
			bool isRegOut=false
			) = 0;
		
		virtual void setInt(
			int paramIndex, 
			int value, 
			bool isRegOut=false
			) = 0;
		
		virtual void setTime(
			int paramIndex, 
			const CDateTime& value, 
			bool isRegOut=false
			) = 0;
		
		virtual void setTimestamp(
			int paramIndex, 
			const CDateTime& value, 
			bool isRegOut=false
			) = 0;
		
		virtual void setLong64(
			int paramIndex, 
			long64_t value, 
			bool isRegOut = false
			) = 0;
		
		virtual bool hasMoreResultsets() = 0;
		
		virtual std::auto_ptr<CResultSet> getNextResultSet() = 0;
		
		virtual char getByte( int index ) = 0;
		
		virtual char getByte( const char* columnName ) = 0;
		
		virtual bool getBytes( 
			int index , 
			char* outBuffer, 
			int& length 
			) = 0;
		
		virtual bool getBytes( 
			const char* columnName , 
			char* outBuffer, 
			int& length 
			) = 0;
		
		virtual std::string getString( 
			int index 
			) = 0;
		
		virtual std::string getString( 
			const char* column 
			) = 0;
		
		virtual int getInt(
			int index 
			) = 0;
		
		virtual int getInt(
			const char* column
			) = 0;
		
		virtual double getDouble(
			int index 
			) = 0;
		
		virtual double getDouble(
			const char* column
			) = 0;
		
		virtual bool isNull(
			int index 
			) = 0;
		
		virtual bool isNull(
			const char* column
			) = 0;
		
		virtual CDateTime getDate(
			int index 
			) = 0;
		
		virtual CDateTime getDate(
			const char* paramName
			) = 0;
		
		virtual CDateTime getTime(
			int index 
			) = 0;
		
		virtual CDateTime getTime(
			const char* paramName 
			) = 0;
		
		virtual CDateTime getTimestamp(
			int index 
			) = 0;
		
		virtual CDateTime getTimestamp(
			const char* paramName 
			) = 0;
		
		virtual long64_t getLong64(
			int index 
			)=0;
		
		virtual long64_t getLong64(
			const char* paramName 
			)=0;
		
		virtual void prepare(
			const char* sql 
			)=0;
		
	};
}

#endif 
