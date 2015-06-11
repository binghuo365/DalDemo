#ifndef _DAF_POOL_CONN_AUTOPTR_H_
#define _DAF_POOL_CONN_AUTOPTR_H_

#include <memory>

#include "poolconnection.h"
#include "connectionpool.h"

namespace DAFrame
{
	template<class T>
		class CPoolConnAutoPtr:public std::auto_ptr<T>
	{
	public :
		CPoolConnAutoPtr(const CPoolConnAutoPtr& Other )
			:std::auto_ptr<T>((std::auto_ptr<T>&)Other)
		{
		}

		CPoolConnAutoPtr():std::auto_ptr<T>(NULL)
		{
		}

		CPoolConnAutoPtr(T* Pointer):std::auto_ptr<T>(Pointer)
		{
		}

		virtual ~CPoolConnAutoPtr()
		{
		
#if defined(_MSC_VER) && (_MSC_VER < 1300)
			T * conn = release();
#else
			T * conn = std::auto_ptr<T>::release();
#endif
			if( NULL != conn)
				conn->putConnection();
		}
	private:
		CPoolConnAutoPtr& operator = (const CPoolConnAutoPtr& Other)
		{
			return *this;
		}
	};
}
#endif
