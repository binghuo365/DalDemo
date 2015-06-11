#ifndef _POOL_CONNECTION_MANAGER_H_
#define _POOL_CONNECTION_MANAGER_H_

#include "publicdef.h"
#include "datetime.h"
#include "poolconnection.h"
#include "poolconnautoptr.h"

namespace DAFrame
{
	class CPoolConnectionManager
	{
	public:
		static CPoolConnAutoPtr<CPoolConnection> getConnection();
		
		static void initialize(
			const char* url , 
			int count , 
			const char * user ,
			const char * pwd );

		static void finalize();
	protected:
		static std::auto_ptr<CConnectionPool> _connPool;
	};
}
#endif