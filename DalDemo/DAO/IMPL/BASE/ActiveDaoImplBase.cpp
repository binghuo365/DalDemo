#include "ActiveDAOImplBase.h"
#include "..\..\..\DAFrame\DAOBASE\poolconnautoptr.h"
#include "..\..\..\DAFrame\DAOBASE\poolconnectionmanager.h"
#include "..\..\..\DAFrame\DAOBASE\daoquerydef.h"
#include "..\..\..\DAFrame\DAOBASE\resultset.h"

DAO::IMPL::CActiveDaoImplBase::CActiveDaoImplBase()

{
    
}
DAO::IMPL::CActiveDaoImplBase::~CActiveDaoImplBase()
{
}

bool DAO::IMPL::CActiveDaoImplBase::get( int id , DAO::Tables::TActive& v , bool update )
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
    std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return get( id , v , stmt.get() , update );
}

void DAO::IMPL::CActiveDaoImplBase::save( Tables::TActive& v )
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    save( v , stmt.get() );
}

bool DAO::IMPL::CActiveDaoImplBase::update( const Tables::TActive& v )
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return update( v , stmt.get() );
}

bool DAO::IMPL::CActiveDaoImplBase::remove( int id )
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return remove( id , stmt.get() );
}

long64_t DAO::IMPL::CActiveDaoImplBase::find(const DAFrame::DAO::SQuery& query, Tables::SeqTActive& v, bool update)
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

bool DAO::IMPL::CActiveDaoImplBase::find(const DAFrame::DAO::SQuery& query, Tables::TActive& v, bool update)
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return find( query , v , stmt.get() , update );
}

long64_t DAO::IMPL::CActiveDaoImplBase::update(const DAFrame::DAO::SeqCmpNode& cmp, const Tables::TActive& v)
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return update( cmp , v , stmt.get() );
}

long64_t DAO::IMPL::CActiveDaoImplBase::update(const DAFrame::DAO::SeqCmpNode& cmp, const DAFrame::DAO::SeqDataNode& seq)
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return update( cmp , seq , stmt.get() );
}

long64_t DAO::IMPL::CActiveDaoImplBase::remove( const DAFrame::DAO::SeqCmpNode& cmp )
{
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn = DAFrame::CPoolConnectionManager::getConnection();
	std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
    return remove( cmp , stmt.get() );
}

bool DAO::IMPL::CActiveDaoImplBase::get(int id, DAO::Tables::TActive& v, DAFrame::CStatement* stmt, bool update, bool usedCached)
{
    std::string sql = _selectBase + " where id = ?";
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    stmt->setInt( 1 , id );
    std::auto_ptr<DAFrame::CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTActive ( v , rs.get() );
        return true;
    }
    return false;
}

void DAO::IMPL::CActiveDaoImplBase::save( DAO::Tables::TActive& v , DAFrame::CStatement* stmt , bool usedCached )
{
    stmt->prepare( _insertBase.c_str() );
    __writeTActive( v , stmt );
    stmt->executeUpdate();
    v.id = (int)stmt->getInsertID( "s_t_active" );
}

bool DAO::IMPL::CActiveDaoImplBase::update( const DAO::Tables::TActive& v , DAFrame::CStatement* stmt , bool usedCached )
{
    stmt->prepare( (_updateBase + " where id = ?").c_str() );
    __writeTActive( v , stmt );
    stmt->setInt( 11 , v.id );
    return stmt->executeUpdate() > 0;
}

long64_t DAO::IMPL::CActiveDaoImplBase::update( const DAFrame::DAO::SeqCmpNode& cmp , const DAFrame::DAO::SeqDataNode& seq , DAFrame::CStatement* stmt , bool usedCached )
{
    std::string sql = "update t_active";
    sql += makeUpdate( seq );
    sql += makeQuery( cmp );
    stmt->prepare( sql.c_str() );
    this->writeStmt( 1 , seq , stmt );
    this->writeStmt( (int)seq.size() + 1 , cmp , stmt );
    return stmt->executeUpdate();
}

bool DAO::IMPL::CActiveDaoImplBase::remove( int id , DAFrame::CStatement* stmt , bool usedCached )
{
    stmt->prepare( "delete from t_active where id = ? ");
    stmt->setInt( 1 , id );
    return stmt->executeUpdate() > 0;
}

long64_t DAO::IMPL::CActiveDaoImplBase::find( const DAFrame::DAO::SQuery& query , DAO::Tables::SeqTActive& v , DAFrame::CStatement* stmt , bool update , bool usedCached )
{
    v.clear();
    std::string sqlWhere = makeQuery( query.cmpNodes );
    long64_t count = 0;
	if (query.countType & DAFrame::DAO::FIND_COUNT_TYPE_WITH_COUNT)
    {
        stmt->prepare( ("select count(*) as count1 from t_active" + sqlWhere ).c_str() );
        writeStmt( 1 , query.cmpNodes , stmt );
        std::auto_ptr<DAFrame::CResultSet> rs = stmt->executeQuery();
        if( rs->next() )
            count = rs->getLong64( 1 );
    }
	if (!(query.countType & DAFrame::DAO::FIND_COUNT_TYPE_WITH_DATA))
        return count;
    std::string sql = _selectBase + sqlWhere + makeOrder( query );
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    writeStmt( 1 , query.cmpNodes , stmt );
    std::auto_ptr<DAFrame::CResultSet> rs = stmt->executeQuery();
    DAO::Tables::TActive node;
    while( rs->next() )
    {
        __readTActive( node , rs.get() );
        v.push_back( node );
    }
    return count;
}

bool DAO::IMPL::CActiveDaoImplBase::find( const DAFrame::DAO::SQuery& query , DAO::Tables::TActive& v , DAFrame::CStatement* stmt , bool update , bool usedCached )
{
    std::string sqlWhere = makeQuery( query.cmpNodes );
    std::string sql = _selectBase + sqlWhere + makeOrder( query );
    if( update )
    {
        sql += " for update";
    }
    stmt->prepare( sql.c_str() );
    writeStmt( 1 , query.cmpNodes , stmt );
    std::auto_ptr<DAFrame::CResultSet> rs = stmt->executeQuery();
    if( rs->next() )
    {
        __readTActive( v , rs.get() );
        return true;
    }
    return false;
}

long64_t DAO::IMPL::CActiveDaoImplBase::update( const DAFrame::DAO::SeqCmpNode& cmp , const DAO::Tables::TActive& v , DAFrame::CStatement* stmt , bool usedCached )
{
    stmt->prepare( ( _updateBase + makeQuery( cmp ) ).c_str() );
    __writeTActive( v , stmt );
    writeStmt( _columnCount , cmp , stmt );
    return stmt->executeUpdate();
}

long64_t DAO::IMPL::CActiveDaoImplBase::remove( const DAFrame::DAO::SeqCmpNode& cmp , DAFrame::CStatement* stmt , bool usedCached )
{
    stmt->prepare( ( "delete from t_active" + makeQuery( cmp ) ).c_str() );
    writeStmt( 1 , cmp , stmt );
    return stmt->executeUpdate();
}


const int DAO::IMPL::CActiveDaoImplBase::_columnCount = 11;

const std::string DAO::IMPL::CActiveDaoImplBase::_selectBase = 
"select id,type,name,status,start_dt,end_dt,loop_interval,start_date,"
"end_date,day_of_week,js_str from t_active";

const std::string DAO::IMPL::CActiveDaoImplBase::_updateBase = 
"update t_active set type=?,name=?,status=?,start_dt=?,end_dt=?,"
"loop_interval=?,start_date=?,end_date=?,day_of_week=?,js_str=?";

const std::string DAO::IMPL::CActiveDaoImplBase::_insertBase = 
"insert into t_active ( type,name,status,start_dt,end_dt,loop_interval,"
"start_date,end_date,day_of_week,js_str) values (?,?,?,?,?,?,?,"
"?,?,?)";

const std::string DAO::IMPL::CActiveDaoImplBase::_deleteBase = 
"delete from t_active";

void DAO::IMPL::CActiveDaoImplBase::__readTActive( DAO::Tables::TActive& outV , DAFrame::CResultSet* rs )
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

void DAO::IMPL::CActiveDaoImplBase::__writeTActive( const DAO::Tables::TActive& inV , DAFrame::CStatement* stmt )
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
