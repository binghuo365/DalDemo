#ifndef _ACTIVE_DAO_BASE_H_
#define _ACTIVE_DAO_BASE_H_

#include "../DAO/TActive.h"
#include "../../DAFrame/DAOBASE/DAOquerydef.h"

namespace DAO
{
    class IActiveDaoBase
    {
    public:
        IActiveDaoBase();
		virtual ~IActiveDaoBase();
        virtual bool get( int id , DAO::Tables::TActive& v , bool update = false ) = 0;
		virtual void save(DAO::Tables::TActive& v) = 0;
		virtual bool update(const DAO::Tables::TActive& v) = 0;
        virtual bool remove( int id ) = 0;
        
		virtual long64_t find(const DAFrame::DAO::SQuery& query, DAO::Tables::SeqTActive& v, bool update = false) = 0;
		virtual bool find(const DAFrame::DAO::SQuery& query, DAO::Tables::TActive& v, bool update = false) = 0;
		virtual long64_t update(const DAFrame::DAO::SeqCmpNode& cmp, const DAO::Tables::TActive& v) = 0;
		virtual long64_t update(const DAFrame::DAO::SeqCmpNode& cmp, const DAFrame::DAO::SeqDataNode& seq) = 0;
		virtual long64_t remove(const DAFrame::DAO::SeqCmpNode& cmp) = 0;
        
        const static std::string _tableName;
        const static std::string _id;
        const static std::string _type;
        const static std::string _name;
        const static std::string _status;
        const static std::string _startDt;
        const static std::string _endDt;
        const static std::string _loopInterval;
        const static std::string _startDate;
        const static std::string _endDate;
        const static std::string _dayOfWeek;
        const static std::string _jsStr;
    };
}
#endif
