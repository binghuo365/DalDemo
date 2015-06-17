#ifndef _ACTIVE_DAO_BASE_IMPL_H_
#define _ACTIVE_DAO_BASE_IMPL_H_
#include "../../ActiveDao.h"
#include "../../../DAFrame/DAOBASE/publicdef.h"
#include "../../../DAFrame/DAOBASE/daobase.h"

namespace DAO
{
    namespace IMPL
    {
        class CActiveCached;
        class CActiveDaoImplBase
                :public DAO::IActiveDao,
				public DAFrame::DAO::CDaoBase
        {
        public:
            CActiveDaoImplBase();
            virtual ~CActiveDaoImplBase();
            virtual bool get( int id , DAO::Tables::TActive& v , bool update = false );
			virtual void save(DAO::Tables::TActive& v);
			virtual bool update(const DAO::Tables::TActive& v);
            virtual bool remove( int id );
            
			virtual long64_t find(const DAFrame::DAO::SQuery& query, DAO::Tables::SeqTActive& v, bool update = false);
			virtual bool find(const DAFrame::DAO::SQuery& query, DAO::Tables::TActive& v, bool update = false);
			virtual long64_t update(const DAFrame::DAO::SeqCmpNode& cmp, const DAO::Tables::TActive& v);
            virtual long64_t update( const DAFrame::DAO::SeqCmpNode& cmp , const DAFrame::DAO::SeqDataNode& seq );
            virtual long64_t remove( const DAFrame::DAO::SeqCmpNode& cmp );
            
			virtual bool get(int id, DAO::Tables::TActive& v, DAFrame::CStatement* stmt, bool update = false, bool usedCached = true);
			virtual void save(DAO::Tables::TActive& v, DAFrame::CStatement* stmt, bool usedCached = true);
			virtual bool update(const DAO::Tables::TActive& v, DAFrame::CStatement* stmt, bool usedCached = true);
			virtual bool remove(int id, DAFrame::CStatement* stmt, bool usedCached = true);
            
			virtual long64_t find(const DAFrame::DAO::SQuery& query, Tables::SeqTActive& v, DAFrame::CStatement* stmt, bool update = false, bool usedCached = true);
			virtual bool find(const DAFrame::DAO::SQuery& query, Tables::TActive& v, DAFrame::CStatement* stmt, bool update = false, bool usedCached = true);
			virtual long64_t update(const DAFrame::DAO::SeqCmpNode& cmp, const DAO::Tables::TActive& v, DAFrame::CStatement* stmt, bool usedCached = true);
			virtual long64_t update(const DAFrame::DAO::SeqCmpNode& cmp, const DAFrame::DAO::SeqDataNode& seq, DAFrame::CStatement* stmt, bool usedCached = true);
            virtual long64_t remove( const DAFrame::DAO::SeqCmpNode& cmp , DAFrame::CStatement* stmt , bool usedCached = true );
            CActiveCached* getCached();
            
            
        public:
            const static int _columnCount;
            const static std::string _selectBase;
            const static std::string _updateBase;
            const static std::string _insertBase;
            const static std::string _deleteBase;
			void static __readTActive(Tables::TActive& outV, DAFrame::CResultSet* rs);
			void static __writeTActive(const Tables::TActive& outV, DAFrame::CStatement* stmt);
        };
    }
}
#endif
