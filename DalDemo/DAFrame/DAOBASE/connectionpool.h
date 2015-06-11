#ifndef _DAF_CONNECTION_POOL_H_
#define _DAF_CONNECTION_POOL_H_

#include <vector>
#include <string>


namespace DAFrame
{
	template <class T>
	class CPoolConnAutoPtr;
	
	class CConnection;
	class CConnectionManager;
	class CPoolConnection;

	class CConnectionPool
	{
		friend class CConnectionManager;
		friend class CPoolConnection;
	public:
		CPoolConnAutoPtr<CPoolConnection> getConnection(const long waitMillis = 0);    
		
		~CConnectionPool();

		void keepActive();
		
	protected:
		
		void putConnection( CPoolConnection* conn );

		CPoolConnection* getIdleConnection();
		
	public:
		CConnectionPool(
			const char* url, 
			int maxConnection,
			const char* user ="",
			const char* userPwd="" , 
			int minConnctions = 8
			);
		
	private:
		std::vector<CPoolConnection*> _connections;
		
		int _maxConnections;
		
		int _connectionCount;
		
		int _lastUserIndex;
		
		int _minConnections;
		
		int _idleConnectionCount;
		
		std::string _url;
		
		std::string _user;
		
		std::string _userPwd;
	};
}

#endif
