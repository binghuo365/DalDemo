#ifndef _DAF_DB_MYSQLDATA_H_
#define _DAF_DB_MYSQLDATA_H_
#include <Winsock2.h>
#include "../DAOBASE/publicdef.h"
#include "string"
#include "mysql.h"

#ifdef DAF_USED_MYSQL

namespace DAFrame
{
	namespace mysql
	{
		class CMetaData
		{
		private :
			MYSQL_BIND _param;
		public :
			CMetaData();
			~CMetaData();
			MYSQL_BIND* getMYSQL_BIND();
			void clear();
		};

		class CResultData
		{
		public :
			EDATATYPE _dataType;
			std::string _columnName;
		};
	}
}

#endif

#endif
