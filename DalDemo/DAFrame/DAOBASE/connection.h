#ifndef _DBF_CONNECTION_H_
#define _DBF_CONNECTION_H_

#include <string>
#include <memory>
#include "transaction.h"

namespace DAFrame
{
	class CStatement;
	class CCallableStatement;
	class CConnectionImpl;
	class CTransaction;

	class CConnection
	{
		friend class CPoolConnection;
	public:
		virtual ~CConnection();
		CConnection();
		CConnection(CConnectionImpl * connImpl );		
		
		virtual void setAutoCommit( bool autoCommit );
		
		virtual bool getAutoCommit();
		
		virtual bool begin( bool cashed = true );
		
		virtual bool commit( bool cashed = true );
		
		virtual bool rollback( bool cashed = true );
		
		virtual bool connect();
		
		virtual bool reconnect(); 
		
		virtual void close();
		
		virtual bool isClosed();

		virtual std::auto_ptr< CStatement > createStatement();

		virtual std::auto_ptr< CStatement > prepareStatement( const char* sql );
		
		virtual std::auto_ptr< CCallableStatement > prepareCall(const char* sql );
		
		virtual void setTransactionIsolation(int level );
		
		virtual bool keepActive();
		
		virtual std::auto_ptr<CConnection> clone();
		
		virtual void setConnctionImpl( CConnectionImpl *connImpl );
		
		virtual CConnectionImpl* getConnctionImpl();

		virtual bool setEncoding(const char * encode = "utf-8");
		
		virtual int getErrNo() const;
		
		virtual const char * getError() const;
		
	protected:
		DAFrame::CConnectionImpl *_connImpl;
	};
}

#endif 
