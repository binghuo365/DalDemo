#ifndef _DFA_DB_MYSQLCONN_H_
#define _DFA_DB_MYSQLCONN_H_
#include <Winsock2.h>
#include "../DAOBASE/publicdef.h"

#ifdef DAF_USED_MYSQL

#include "../DAOBASE/publicdef.h"
#include "../DAOBASE/connectionimpl.h"

#include <windows.h>
#include <mysql.h>

namespace DAFrame
{
	namespace mysql
	{
		
		class CMySQLResultSet;
		class CMySQLStatement;
		
		class CMySQLConnection
			:public CConnectionImpl
		{
			friend class CMySQLStatement;
			friend class CMySQLResultSet;
			friend class CMySQLCallableStatement;
		protected :
			//mysql c api
			MYSQL* _conn;
			//user name
			std::string _userName;
			//pass word
			std::string _passWord;
			//database
			std::string _database;
			//host
			std::string _host;
			//port
			unsigned short _port;
			//connected
			bool _connected;
			//autocommit
			bool _autoCommit;
			//is begin
			bool _begin;
			//the encoding
			std::string _encoding;
		private:
			//the stmt
			DAFrame::mysql::CMySQLStatement* _stmt;
		public :

			CMySQLConnection(const std::string& host,
				unsigned short port = 3306,
				const std::string& dataBase = "",
				const std::string& userName = "",
				const std::string& password = "",
				const std::string& encoding="utf8"
				);

			CMySQLConnection();

			virtual ~CMySQLConnection();

			CConnectionImpl* clone();

			std::auto_ptr<CStatement> createStatement();

			void setAutoCommit(bool bAutoCommit);

			bool getAutoCommit();

			bool begin();

			bool commit();

			bool rollback();

			bool connect();

			bool reconnect();

			void close();

			bool isClosed();

			std::auto_ptr<CStatement> prepareStatement(const char* sql );

			std::auto_ptr<CCallableStatement> prepareCall(const char* sql );

			void setTransactionIsolation(int level);

			bool keepActive();

			virtual bool setEncoding(const char * encode = "utf8");

			virtual bool setConnectString(
				const char * connString , 
				const char * userName , 
				const char * userPwd
				);

			virtual int getErrNo() const;
			virtual const char* getError() const;

			virtual void clearStmt( CMySQLStatement* _stmt );

		public:
			/**
			* to initialize connection
			*/
			static void initialize(const char * encoding = "utf8",
				const bool regist = true);
			/**
			* to finalize connection
			*/
			static void finalize();
		private:
			static char _defultEncoding[];
	};
}// namespace avocado_mysql
}
#endif
#endif
