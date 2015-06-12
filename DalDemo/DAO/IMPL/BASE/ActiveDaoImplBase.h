#ifndef _ACTIVE_DAO_BASE_IMPL_H_
#define _ACTIVE_DAO_BASE_IMPL_H_
#include "Dao/ActiveDao.h"
#include "framework/db/dbpublic.h"
#include "framework/db/dao/daobase.h"
namespace Dao
{
    namespace Impl
    {
        class CActiveCached;
        class CActiveDaoImplBase
                :public Dao::IActiveDao,
                public cdf::dao::CDaoBase
        {
        public:
            CActiveDaoImplBase();
            virtual ~CActiveDaoImplBase();
            virtual bool get( int id , Message::DB::Tables::TActive& v , bool update = false );
            virtual void save( Message::DB::Tables::TActive& v );
            virtual bool update( const Message::DB::Tables::TActive& v );
            virtual bool remove( int id );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::DB::Tables::SeqTActive& v , bool update = false );
            virtual bool find( const cdf::dao::SQuery& query , Message::DB::Tables::TActive& v , bool update = false );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::DB::Tables::TActive& v);
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp );
            
            virtual bool get( int id , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual void save( Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool update( const Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool usedCached = true );
            virtual bool remove( int id , cdf::CStatement* stmt , bool usedCached = true );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::DB::Tables::SeqTActive& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual bool find( const cdf::dao::SQuery& query , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update = false , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::DB::Tables::TActive& v, cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached = true );
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached = true );
            CActiveCached* getCached();
            
            
        public:
            const static int _columnCount;
            const static std::string _selectBase;
            const static std::string _updateBase;
            const static std::string _insertBase;
            const static std::string _deleteBase;
            void static __readTActive( Message::DB::Tables::TActive& outV , cdf::CResultSet* rs );
            void static __writeTActive( const Message::DB::Tables::TActive& outV , cdf::CStatement* stmt );
        
        private:
            CActiveCached *_cached;
            
        };
    }
}
#endif
