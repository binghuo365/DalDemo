#if !defined(_CCONNECTIONMANAGER_H_)
#define _CCONNECTIONMANAGER_H_

#include "publicdef.h"
#include "connectionimpl.h"

#include <vector>
#include <string>
#include <map>

namespace DAFrame
{
	class CConnection;
	class CConnectionPool;

	class CConnectionManager
	{
	private:
	public:
		static std::auto_ptr<CConnection> getConnection(
			const char* connectionURL,
			const char* userName="",
			const char* userPwd=""
			);

		static std::auto_ptr<CConnectionPool> getConnectionPool(
			const char* pConnectionURL,
			int nMaxConnections,
			const char* userName="",
			const char* userPwd=""
			);

		static void registProtocol(
			const char * pProtoclName ,
			CConnectionImpl * pConnImpl
			);

		static void unregistProtocol(
			const char * pProtoclName
			);

		static void finalize();

		static void parseProtocol(
			std::vector<std::string>& params,
			const char* connectionURL
			);

	protected:
		CConnectionManager(){};
		~CConnectionManager(){};
		static std::auto_ptr< std::map< std::string , CConnectionImpl*> > _connPool;
	};
}

#endif
