#ifndef _DBF_CONNECTION_IMPL_H_
#define _DBF_CONNECTION_IMPL_H_
#include "statement.h"
namespace DAFrame
{
	class CStatement;
	class CCallableStatement;

	class CConnectionImpl
	{
	public:
		virtual ~CConnectionImpl(){};

		CConnectionImpl(){}

		virtual std::auto_ptr< CStatement > createStatement() = 0;

		virtual void setAutoCommit(bool bAutoCommit) = 0;

		virtual bool getAutoCommit() = 0;

		virtual bool begin() = 0;

		virtual bool commit() = 0;

		virtual bool rollback() = 0;

		virtual bool connect() = 0;

		virtual bool reconnect() = 0;

		virtual void close() = 0;

		virtual bool isClosed() = 0;

		virtual std::auto_ptr<CStatement> prepareStatement(const char* pSQL) = 0;

		virtual std::auto_ptr< CCallableStatement > prepareCall(const char* pSQL) = 0;

		virtual void setTransactionIsolation(int nLevel) = 0;

		virtual bool keepActive() = 0;

		virtual CConnectionImpl* clone() = 0 ;

		virtual bool setConnectString(
			const char * pConnString ,
			const char * pUserName ,
			const char * pUserPwd
			) = 0;

		virtual bool setEncoding(const char * pEncode = "utf-8") = 0;

		virtual int getErrNo() const = 0;

		virtual const char * getError() const = 0;
};
}
#endif
