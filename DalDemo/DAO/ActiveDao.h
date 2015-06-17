#ifndef _ACTIVE_DAO_H_
#define _ACTIVE_DAO_H_
#include "BASE/ActiveDaoBase.h"
namespace DAO
{
    class IActiveDao
            :public IActiveDaoBase
    {
    public:
        IActiveDao();
        virtual ~IActiveDao();

		virtual void load(DAO::Tables::SeqTActive& tActives) = 0;
    };
}
#endif
