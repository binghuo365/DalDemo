#ifndef _ACTIVE_DAO_BASE_H_
#define _ACTIVE_DAO_BASE_H_
#include "Message/DB/Tables/TActive.h"
#include "framework/db/dao/daoquerydef.h"
#include "framework/db/cached/cacheddao.h"
namespace Dao
{
    class IActiveDaoBase
    {
    public:
        IActiveDaoBase();
        virtual ~IActiveDaoBase();
        virtual bool get( int id , Message::DB::Tables::TActive& v , bool update = false ) = 0;
        virtual void save( Message::DB::Tables::TActive& v ) = 0;
        virtual bool update( const Message::DB::Tables::TActive& v ) = 0;
        virtual bool remove( int id ) = 0;
        
        virtual long64_t find( const cdf::dao::SQuery& query , Message::DB::Tables::SeqTActive& v , bool update = false ) = 0;
        virtual bool find( const cdf::dao::SQuery& query , Message::DB::Tables::TActive& v , bool update = false ) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const Message::DB::Tables::TActive& v) = 0;
        virtual long64_t update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq ) = 0;
        virtual long64_t remove( const cdf::dao::SeqCmpNode& cmp ) = 0;
        
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
