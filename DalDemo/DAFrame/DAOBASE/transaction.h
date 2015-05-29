#ifndef _CDF_TRANSACTION_H_
#define _CDF_TRANSACTION_H_

#include <string>
#include <memory>

#include "connection.h"

namespace DAFrame
{
	class CTransaction
	{
	public:
		virtual ~CTransaction();
		CTransaction();

		virtual bool begin() = 0;

		virtual bool commit() = 0;

		virtual bool rollback() = 0;

		virtual bool isBegin() = 0;

		virtual CTransaction* clone() = 0;
	protected:
	};
}

#endif 
