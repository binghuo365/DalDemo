#include "Dao/Impl/Base/ActiveDaoImplBase.h"
#include "Dao/Impl/Base/ActiveCached.h"
#include "framework/db/cached/cachedmanager.h"

using namespace cdf;
using namespace cdf::dao;
Dao::Impl::CActiveDaoImplBase::CActiveDaoImplBase()

{
    _cached = dynamic_cast< Dao::Impl::CActiveCached* >( cdf::cached::CCachedManager::instance()->getTableCached( "t_active" ) ); 
    
}
Dao::Impl::CActiveDaoImplBase::~CActiveDaoImplBase()
{
}

bool Dao::Impl::CActiveDaoImplBase::get( int id , Message::DB::Tables::TActive& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return get( id , v , stmt.get() , update );
}

void Dao::Impl::CActiveDaoImplBase::save( Message::DB::Tables::TActive& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    save( v , stmt.get() );
}

bool Dao::Impl::CActiveDaoImplBase::update( const Message::DB::Tables::TActive& v )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( v , stmt.get() );
}

bool Dao::Impl::CActiveDaoImplBase::remove( int id )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( id , stmt.get() );
}

long64_t Dao::Impl::CActiveDaoImplBase::find( const cdf::dao::SQuery& query , Message::DB::Tables::SeqTActive& v , bool update )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

bool Dao::Impl::CActiveDaoImplBase::find( const cdf::dao::SQuery& query , Message::DB::Tables::TActive& v , bool update  )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

long64_t Dao::Impl::CActiveDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::DB::Tables::TActive& v)
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , v , stmt.get() );
}

long64_t Dao::Impl::CActiveDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return update( cmp , seq , stmt.get() );
}

long64_t Dao::Impl::CActiveDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt = conn->createStatement();
    return remove( cmp , stmt.get() );
}

bool Dao::Impl::CActiveDaoImplBase::get( int id , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->get( id , v , stmt , update );
    }
    std::string sql = _selectBase + " where id = ?";
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    stmt->setInt( 1 , id );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTActive ( v , rs.get() );
        return true;
    }
    return false;
}

void Dao::Impl::CActiveDaoImplBase::save( Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() )
    {
        _cached->save( v , stmt );
        return;
    }
    stmt->prepare( _insertBase.c_str() );
    __writeTActive( v , stmt );
    stmt->executeUpdate();
    v.id = (int)stmt->getInsertID( "s_t_active" );
}

bool Dao::Impl::CActiveDaoImplBase::update( const Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( v , stmt );
    }
    stmt->prepare( (_updateBase + " where id = ?").c_str() );
    __writeTActive( v , stmt );
    stmt->setInt( 11 , v.id );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CActiveDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , seq , stmt );
    }
    std::string sql = "update t_active";
    sql += makeUpdate( seq );
    sql += makeQuery( cmp );
    stmt->prepare( sql.c_str() );
    this->writeStmt( 1 , seq , stmt );
    this->writeStmt( (int)seq.size() + 1 , cmp , stmt );
    return stmt->executeUpdate();
}

bool Dao::Impl::CActiveDaoImplBase::remove( int id , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( id , stmt );
    }
    stmt->prepare( "delete from t_active where id = ? ");
    stmt->setInt( 1 , id );
    return stmt->executeUpdate() > 0;
}

long64_t Dao::Impl::CActiveDaoImplBase::find( const cdf::dao::SQuery& query , Message::DB::Tables::SeqTActive& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->find( query , v , stmt , update );
    }
    v.clear();
    std::string sqlWhere = makeQuery( query.cmpNodes );
    long64_t count = 0;
    if( query.countType & FIND_COUNT_TYPE_WITH_COUNT )
    {
        stmt->prepare( ("select count(*) as count1 from t_active" + sqlWhere ).c_str() );
        writeStmt( 1 , query.cmpNodes , stmt );
        std::auto_ptr<CResultSet> rs = stmt->executeQuery();
        if( rs->next() )
            count = rs->getLong64( 1 );
    }
    if( !(query.countType & FIND_COUNT_TYPE_WITH_DATA) )
        return count;
    std::string sql = _selectBase + sqlWhere + makeOrder( query );
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    writeStmt( 1 , query.cmpNodes , stmt );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    Message::DB::Tables::TActive node;
    while( rs->next() )
    {
        __readTActive( node , rs.get() );
        v.push_back( node );
    }
    return count;
}

bool Dao::Impl::CActiveDaoImplBase::find( const cdf::dao::SQuery& query , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->find( query , v , stmt , update );
    }
    std::string sqlWhere = makeQuery( query.cmpNodes );
    std::string sql = _selectBase + sqlWhere + makeOrder( query );
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    writeStmt( 1 , query.cmpNodes , stmt );
    std::auto_ptr<CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTActive( v , rs.get() );
        return true;
    }
    return false;
}

long64_t Dao::Impl::CActiveDaoImplBase::update( const cdf::dao::SeqCmpNode& cmp , const Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->update( cmp , v , stmt );
    }
    stmt->prepare( ( _updateBase + makeQuery( cmp ) ).c_str() );
    __writeTActive( v , stmt );
    writeStmt( _columnCount , cmp , stmt );
    return stmt->executeUpdate();
}

long64_t Dao::Impl::CActiveDaoImplBase::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt , bool usedCached )
{
    if( usedCached && _cached && _cached->isUsedCached() && !_cached->isNagtiveOnly() && !_cached->isInsertOnly() )
    {
        return _cached->remove( cmp , stmt );
    }
    stmt->prepare( ( "delete from t_active" + makeQuery( cmp ) ).c_str() );
    writeStmt( 1 , cmp , stmt );
    return stmt->executeUpdate();
}


const int Dao::Impl::CActiveDaoImplBase::_columnCount = 11;

const std::string Dao::Impl::CActiveDaoImplBase::_selectBase = 
"select id,type,name,status,start_dt,end_dt,loop_interval,start_date,"
"end_date,day_of_week,js_str from t_active";

const std::string Dao::Impl::CActiveDaoImplBase::_updateBase = 
"update t_active set type=?,name=?,status=?,start_dt=?,end_dt=?,"
"loop_interval=?,start_date=?,end_date=?,day_of_week=?,js_str=?";

const std::string Dao::Impl::CActiveDaoImplBase::_insertBase = 
"insert into t_active ( type,name,status,start_dt,end_dt,loop_interval,"
"start_date,end_date,day_of_week,js_str) values (?,?,?,?,?,?,?,"
"?,?,?)";

const std::string Dao::Impl::CActiveDaoImplBase::_deleteBase = 
"delete from t_active";

void Dao::Impl::CActiveDaoImplBase::__readTActive( Message::DB::Tables::TActive& outV , cdf::CResultSet* rs )
{
    outV.id = rs->getInt( 1 );
    outV.type = rs->getInt( 2 );
    outV.name = rs->getString( 3 );
    outV.status = rs->getInt( 4 );
    outV.startDt = rs->getDate( 5 );
    outV.endDt = rs->getDate( 6 );
    outV.loopInterval = rs->getInt( 7 );
    outV.startDate = rs->getInt( 8 );
    outV.endDate = rs->getInt( 9 );
    outV.dayOfWeek = rs->getString( 10 );
    outV.jsStr = rs->getString( 11 );
}

void Dao::Impl::CActiveDaoImplBase::__writeTActive( const Message::DB::Tables::TActive& inV , cdf::CStatement* stmt )
{
    stmt->setInt( 1 , inV.type );
    stmt->setString( 2 , inV.name );
    stmt->setInt( 3 , inV.status );
    stmt->setDate( 4 , inV.startDt );
    stmt->setDate( 5 , inV.endDt );
    stmt->setInt( 6 , inV.loopInterval );
    stmt->setInt( 7 , inV.startDate );
    stmt->setInt( 8 , inV.endDate );
    stmt->setString( 9 , inV.dayOfWeek );
    stmt->setString( 10 , inV.jsStr );
}

Dao::Impl::CActiveCached* Dao::Impl::CActiveDaoImplBase::getCached()
{
    return _cached;
}