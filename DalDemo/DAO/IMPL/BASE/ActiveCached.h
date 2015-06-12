#ifndef _ACTIVE_DAO_CACHED_H_
#define _ACTIVE_DAO_CACHED_H_
#include "Dao/ActiveDao.h"
#include "framework/db/dbpublic.h"
#include "framework/db/dao/daobase.h"
#include "framework/db/cached/cachednode.h"
#include "framework/db/cached/cachedbase.h"
#include "framework/util/lightlock.h"
#include "framework/db/fastdb/fastdb.h"
#include "framework/util/atomicoperation.h"
#include "set"
#include "map"
namespace Dao
{
    namespace Impl
    {
        class TActiveCached
        {
        public:
            int id;
            int type;
            std::string name;
            int status;
            long64_t startDt;
            long64_t endDt;
            int loopInterval;
            int startDate;
            int endDate;
            std::string dayOfWeek;
            std::string jsStr;
            FASTDB_NS::dbFieldDescriptor* dbDescribeComponents(FASTDB_NS::dbFieldDescriptor*);
            static FASTDB_NS::dbTableDescriptor dbDescriptor;
            void __update( const Message::DB::Tables::TActive& v );
            void __save( Message::DB::Tables::TActive& v ) const;
        };
        class CActiveCached
                :public cdf::cached::CCachedDao,
                public cdf::cached::CCachedBase
        {
        public:
            typedef cdf::cached::CCachedNode< Message::DB::Tables::TActive> MEM_NODE;
            typedef cdf::CHandle< MEM_NODE > MEM_NODE_PTR;
            typedef std::map<int,MEM_NODE_PTR> MEM_NODE_MAP;
            typedef std::list<MEM_NODE_PTR> MEM_NODE_LIST;
            typedef std::map< cdf::CTransaction* , MEM_NODE_MAP > TRANSACTION_MAP;
            
            virtual bool get( int id , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update = false );
            virtual void save( Message::DB::Tables::TActive& v , cdf::CStatement* stmt );
            virtual bool update( const Message::DB::Tables::TActive& v , cdf::CStatement* stmt );
            virtual bool remove( int id , cdf::CStatement* stmt );
            
            virtual long64_t find( const cdf::dao::SQuery& query , Message::DB::Tables::SeqTActive& v , cdf::CStatement* stmt , bool update = false );
            virtual bool find( const cdf::dao::SQuery& query , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update = false );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::DB::Tables::TActive& v, cdf::CStatement* stmt );
            virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt);
            virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt );
            
            virtual int getTotalCount();
            virtual void clear( cdf::CStatement* stmt );
            virtual void load( cdf::CStatement* stmt );
            virtual void flush( cdf::CStatement* stmt );
            virtual void rollback( cdf::CTransaction* tx );
            virtual void commit( cdf::CTransaction* tx );
            virtual void nagtive( cdf::CStatement* stmt );
            virtual void unnagtive( cdf::CStatement* stmt );
            virtual void cached( const cdf::dao::SQuery& query , cdf::CStatement* stmt );
            virtual void cached( Message::DB::Tables::SeqTActive& v );
            virtual void evict( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt );
            
            static void regist();
            
        private:
            virtual MEM_NODE_PTR getNagtive( cdf::CStatement* stmt );
            virtual void __registToTx( 
            	cdf::CTransaction* tx , 
            	const TActiveCached& table,
            	cdf::cached::ECachedUpdateModel model
            	);
            virtual void __update(
            	TActiveCached& v,
            	const cdf::dao::SeqDataNode& seq 
            	);
            TRANSACTION_MAP _transactionNodes;
            MEM_NODE_MAP _flushMap;
            MEM_NODE_LIST _nagtiveList;
            cdf::CAtomic _id;
            cdf::CLightLock _lock;
            cdf::CLightLock _nagtiveLock;
            static cdf::CAutoRun _autoRun;
        };
    }
}
#endif

void cached( Message::DB::Tables::SeqTActive& v );