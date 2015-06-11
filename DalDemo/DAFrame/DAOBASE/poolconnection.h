#ifndef _POOL_CONNECTION_H_
#define _POOL_CONNECTION_H_

#include "connection.h"

namespace DAFrame
{
	class CConnectionPool;
	
	class CPoolConnection
		:public CConnection
	{
	public:
		
		void close();
		
		bool isClosed();
		
		~CPoolConnection();
		
		std::auto_ptr<CConnection> clone();
		
		virtual int getErrNo() const
		{
			return 0;
		};
		
		virtual const char * getError() const
		{
			return NULL;
		}
		
		void putConnection();

		void setCached( bool cached )
		{
			_cached = cached;
		}
		bool isCached() const
		{
			return _cached;
		}
	protected:
		friend class ::DAFrame::CConnectionPool;
		CPoolConnection( 
			CConnectionImpl* connImpl ,
			CConnectionPool* connectionPool 
			);
		
		CConnectionPool* _connectionPool;
		
		bool _isIdle;

		bool _cached;
	};
}

#endif
