#ifndef _CDF_SQL_EXCEPTION_H_
#define _CDF_SQL_EXCEPTION_H_

#include <string>
#include <map>
#include "exception.h"
namespace DAFrame
{
	class CSQLError
	{
	public:
		/**
		* the sql error of the db
		*/
		CSQLError (int errorCode , const char* errorDesc)
			: _errorCode(errorCode),
			_errorDesc(errorDesc)
		{
			
		}
		
		/**
		* the sql error of the db
		*/
		int getSQLErrorCode()    { return _errorCode; } 
		
		/**
		* get the error desc
		*/
		const std::string& getSQLDesc() const { return _errorDesc; }
		
	private:
		int         _errorCode;    
		std::string _errorDesc;    
	};
	
	class CSQLException : public CException
	{
	public:
		CSQLException(int errorCode, const char* errorMsg);
		
		virtual ~CSQLException() throw();
		
		/**
		* get the exception
		*/
		const char* what() const;
		
		/**
		* get the sql error
		*/
		const CSQLError& getSQLError();	
	private:
		CSQLError _SQLError;
	};
	
	template <class T>
		void ThrowSQLException(int errorCode,const char* fmt,...)
	{
		char buffer[1024];
		va_list list;
		va_start(list,fmt);
#ifdef WIN32
		int retval = _vsnprintf(buffer,sizeof(buffer)-1,fmt,list);
		if ( retval > 0 )
		{
			buffer[retval] = 0;
		}
		else if ( retval == -1 )
		{
			buffer[sizeof(buffer)-1] = 0;
		}
#elif defined GCC
		//if the linux printf
		int retval = vsnprintf(buffer,sizeof(buffer),fmt, list);
#else
		int retval = vsnprintf(buffer,sizeof(buffer)-1,fmt,list);
		if ( retval > 0 )
		{
			buffer[retval] = 0;
		}
		else if ( retval == -1 )
		{
			buffer[sizeof(buffer)-1] = 0;
		}
#endif
		buffer[sizeof(buffer)-1] = 0 ;
		va_end(list);
		throw T( errorCode ,buffer);
	}
}
#endif // !defined(SQLEXCEPTION_H)