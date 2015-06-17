#ifndef _DAFRAME_EXCEPTION_H_
#define _DAFRAME_EXCEPTION_H_

#include <string>
#include <stdarg.h>
#include <sstream>

namespace DAFrame
{
	enum ECDEErrorCode
	{
		ExceptionCodeSystemBase = 10000,
		ExceptionCodeRMIBase = 20000 ,
		ExceptionCodeUserBase = 30000
	};

	enum ECDEErrorCodeSystem
	{
		ExceptionCodeUnkown = 10000 ,  //ExceptionCodeSystemBaseunkown exception
		ExceptionOutOffMemery = 10001, //out of memory
		ExceptionCodeBase = 10002,     //base exception
		ExceptionCodeStd = 10003,      //the std exception
		ExceptionCodeDateTime = 10004, //the datatime exception
		ExceptionCodeFunction = 10005, //function exception
		ExceptionCodeNullHandle = 10006,  //null handle exception
		ExceptionCodeDB = 10007,          //the db exception
		ExceptionCodeSerialize = 10008,   //serialize exception
		ExceptionCodeLang = 10009,        //lang exception
		ExceptionCodeXml = 10010,         //exception xml
		ExceptionCodeMq = 10011,          //exception xml
		ExceptionCodeReadOnly = 10012           //exception xml
	};

	class CException
		:public std::exception
	{
	public :

		CException( const char* msg = "CException", int code = ExceptionCodeBase )
			:_str( msg ),_code(code)
		{
		}

		CException( const CException& ex)
			:_str(ex._str),_code(ex._code)
		{
		}

		CException& operator = ( const CException& ex )
		{
			_str = ex._str;
			_code = ex._code;
			return *this;
		}

		const char* what() const throw()
		{
			return _str.c_str();
		}

		int code() const
		{
			return _code;
		}

		void setMessage( const std::string& msg )
		{
			_str = msg;
		}

		void setCode( int code )
		{
			_code = code;
		}
	protected:
		std::string _str;
		int _code;  //the exeption code
	};

	class CNullHandleException : public CException
	{
	public :
		CNullHandleException(const char* file , int nline);
		virtual ~CNullHandleException();
	};

#define DAF_THROW_EXCEPTION( E , STR ) \
	{ \
	std::ostringstream stream;\
	stream << STR ; \
	E e( stream.str().c_str() ); \
	throw e;\
	}

#define DAF_THROW_CODE_EXCEPTION( E , CODE , STR ) \
	{ \
	std::ostringstream stream;\
	stream << STR ; \
	E e( stream.str().c_str() , CODE ); \
	throw e;\
	}
}
#endif
