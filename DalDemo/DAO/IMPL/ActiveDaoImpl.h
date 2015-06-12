#ifndef _ACTIVE_DAO_IMPL_H_
#define _ACTIVE_DAO_IMPL_H_
#include "Dao/Impl/Base/ActiveDaoImplBase.h"
namespace Dao
{
    namespace Impl
    {
        class CActiveDaoImpl
                :public CActiveDaoImplBase
        {
        public:
            CActiveDaoImpl();
            virtual ~CActiveDaoImpl();

			virtual void load(Message::DB::Tables::SeqTActive& tActives);
        };
    }
}
#endif
