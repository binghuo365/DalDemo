#ifndef _ACTIVE_DAO_IMPL_H_
#define _ACTIVE_DAO_IMPL_H_
#include "BASE/ActiveDaoImplBase.h"
namespace DAO
{
    namespace IMPL
    {
        class CActiveDaoImpl
                :public CActiveDaoImplBase
        {
        public:
            CActiveDaoImpl();
            virtual ~CActiveDaoImpl();

			virtual void load(DAO::Tables::SeqTActive& tActives);
        };
    }
}
#endif
