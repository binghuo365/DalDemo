#ifndef _ACTIVE_DAO_H_
#define _ACTIVE_DAO_H_
#include "DAFrame/DAOBASE/BASE/ActiveDaoBase.h"
namespace Dao
{
    class IActiveDao
            :public IActiveDaoBase
    {
    public:
        IActiveDao();
        virtual ~IActiveDao();

		virtual void load(Message::DB::Tables::SeqTActive& tActives) = 0;
    };
}
#endif
