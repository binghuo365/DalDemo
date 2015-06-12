#include "Dao/Impl/Base/ActiveCached.h"
#include "Dao/Impl/ActiveDaoImpl.h"
#include "framework/util/exception.h"
#include "framework/db/cached/cachedmanager.h"
#include "framework/db/cached/cachedtransaction.h"
#include "framework/log/loggerutil.h"

using namespace cdf;
using namespace cdf::dao;
using namespace cdf::cached;
using namespace Dao::Impl;
USE_FASTDB_NAMESPACE;

REGISTER( TActiveCached );
cdf::CAutoRun CActiveCached::_autoRun( CActiveCached::regist );

FASTDB_NS::dbFieldDescriptor* 
TActiveCached::dbDescribeComponents(FASTDB_NS::dbFieldDescriptor*)
{
    return
        &(
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("id", (char*)&id-(char*)this , sizeof( id ), FASTDB_NS::HASHED | FASTDB_NS::INDEXED ), id),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("type", (char*)&type-(char*)this , sizeof( type ), 0 ), type),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("name", (char*)&name-(char*)this , sizeof( name ), 0 ), name),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("status", (char*)&status-(char*)this , sizeof( status ), 0 ), status),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("start_dt", (char*)&startDt-(char*)this , sizeof( startDt ), 0 ), startDt),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("end_dt", (char*)&endDt-(char*)this , sizeof( endDt ), 0 ), endDt),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("loop_interval", (char*)&loopInterval-(char*)this , sizeof( loopInterval ), 0 ), loopInterval),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("start_date", (char*)&startDate-(char*)this , sizeof( startDate ), 0 ), startDate),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("end_date", (char*)&endDate-(char*)this , sizeof( endDate ), 0 ), endDate),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("day_of_week", (char*)&dayOfWeek-(char*)this , sizeof( dayOfWeek ), 0 ), dayOfWeek),
        *FASTDB_NS::dbDescribeField(new FASTDB_NS::dbFieldDescriptor("js_str", (char*)&jsStr-(char*)this , sizeof( jsStr ), 0 ), jsStr)
        );
    
}

void
TActiveCached::__update( const Message::DB::Tables::TActive& t )
{
    id = t.id;
    type = t.type;
    name = t.name;
    status = t.status;
    {
        cdf::CDateTime __date( t.startDt );
        __date.clearMillSecond();
        startDt = __date.getTotalMill();
    }
    {
        cdf::CDateTime __date( t.endDt );
        __date.clearMillSecond();
        endDt = __date.getTotalMill();
    }
    loopInterval = t.loopInterval;
    startDate = t.startDate;
    endDate = t.endDate;
    dayOfWeek = t.dayOfWeek;
    jsStr = t.jsStr;
}

void
TActiveCached::__save( Message::DB::Tables::TActive& t ) const 
{
    t.id = id;
    t.type = type;
    t.name = name;
    t.status = status;
    t.startDt.init( startDt );
    t.endDt.init( endDt );
    t.loopInterval = loopInterval;
    t.startDate = startDate;
    t.endDate = endDate;
    t.dayOfWeek = dayOfWeek;
    t.jsStr = jsStr;
}

void Dao::Impl::CActiveCached::regist()
{
    static Dao::Impl::CActiveCached cached;
    cdf::cached::CCachedManager::instance()->registTableCached( "t_active" , &cached );
}

bool Dao::Impl::CActiveCached::get( int id , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update )
{
    dbQuery q;
    q = "id=",(id);
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbCursorType type = dbCursorViewOnly;
    if( update )
    {
        type = dbCursorForUpdate;
    }
    int n = cursor.select( q , type );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        cursor.get()->__save( v );
        return true;
    }
}

void Dao::Impl::CActiveCached::save( Message::DB::Tables::TActive& v , cdf::CStatement* stmt )
{
    CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
    std::auto_ptr<CStatement> stmt1 = conn->createStatement();
    TActiveCached t;
    if( !isInsertOnly() )
    {
        conn->setCached( false );
        conn->begin( false );
        MEM_NODE_PTR nodePtr = getNagtive( stmt1.get() );
        conn->commit( false );
        v.id = nodePtr->getNode().id;
        t.__update( v );
        if( !isNagtiveOnly() )
        {
            dbAnyReference ref;
            CCachedManager::instance()->getDb().insertRecord( 
            	&TActiveCached::dbDescriptor , &ref , &t
            	);
        }
    }
    else
    {
        v.id = ++ _id;
        t.__update( v );
    }
    __registToTx( 
    	stmt->getConnection()->getTransaction() , 
    	t ,
    	cdf::cached::ECachedUpdateModelAdd
    	);
}

bool Dao::Impl::CActiveCached::update( const Message::DB::Tables::TActive& t , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "id=",(t.id);
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    int n = cursor.select( q , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        cursor.get()->__update( t );
        cursor.update();
        __registToTx( 
        	stmt->getConnection()->getTransaction() , 
        	*cursor.get() ,
        	cdf::cached::ECachedUpdateModelUpdate
        	);
        return true;
    }
}

long64_t Dao::Impl::CActiveCached::update( const cdf::dao::SeqCmpNode& cmp , const cdf::dao::SeqDataNode& seq , cdf::CStatement* stmt )
{
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( cmp , cachedCmpNodes , query );
    int n = cursor.select( query , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        do
        {
            __update( *cursor.get() , seq );
            cursor.update();
            __registToTx( 
            stmt->getConnection()->getTransaction() , 
            *cursor.get() ,
            cdf::cached::ECachedUpdateModelUpdate 
            );
        }
        while( cursor.next() );
    }
    return n;
}

bool Dao::Impl::CActiveCached::remove( int id , cdf::CStatement* stmt )
{
    dbQuery q;
    q = "id=",(id);
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    int n = cursor.select( q , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        do
        {
            __registToTx( 
            	stmt->getConnection()->getTransaction() , 
            	*cursor.get() ,
            	cdf::cached::ECachedUpdateModelDelete
            	);
        }
        while( cursor.next() );
        cursor.removeAllSelected();
        return true;
    }
}

long64_t Dao::Impl::CActiveCached::find( const cdf::dao::SQuery& query , Message::DB::Tables::SeqTActive& v , cdf::CStatement* stmt , bool update )
{
    v.clear();
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( query.cmpNodes , cachedCmpNodes , query1 );
    std::string order;
    makeOrder( query.orderType , query1 , order );
    dbCursorType type = dbCursorViewOnly;
    if( update )
    {
        type = dbCursorForUpdate;
    }
    int n = cursor.select( query1 , type );
    if( query.countType == cdf::dao::FIND_COUNT_TYPE_WITH_COUNT )
    {
        return n;
    }
    if( 0 == n )
    {
        return 0;
    }
    else
    {
        int i = 0;
        Message::DB::Tables::TActive table;
        do
        {
            if( query.startIndex == query.endIndex && query.startIndex == 0 )
            {
                cursor.get()->__save( table );
                v.push_back( table );
            }
            else
            {
                if( i >= query.startIndex )
                {
                    if( i < query.endIndex )
                    {
                        cursor.get()->__save( table );
                        v.push_back( table );
                    }
                    else
                    {
                        break;
                    }
                }
                i ++;
            }
        }
        while( cursor.next() );
    }
    if( query.countType == cdf::dao::FIND_COUNT_TYPE_WITH_DATA )
    {
        return 0;
    }
    return n;
}

bool Dao::Impl::CActiveCached::find( const cdf::dao::SQuery& query , Message::DB::Tables::TActive& v , cdf::CStatement* stmt , bool update )
{
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( query.cmpNodes , cachedCmpNodes , query1 );
    dbCursorType type = dbCursorViewOnly;
    if( update )
    {
        type = dbCursorForUpdate;
    }
    int n = cursor.select( query1 , type );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        cursor.get()->__save( v );
        return true;
    }
}

long64_t Dao::Impl::CActiveCached::update( const cdf::dao::SeqCmpNode& cmp , const Message::DB::Tables::TActive& v , cdf::CStatement* stmt )
{
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    makeQuery( cmp , cachedCmpNodes , query );
    int n = cursor.select( query , dbCursorForUpdate );
    if( 0 == n )
    {
        return false;
    }
    else
    {
        do
        {
            int id = cursor.get()->id;
            cursor.get()->__update( v );
            cursor.get()->id = id;
            __registToTx( 
            stmt->getConnection()->getTransaction() , 
            *cursor.get() ,
            cdf::cached::ECachedUpdateModelUpdate );
            cursor.update();
        }
        while( cursor.next() );
    }
    return n;
}

long64_t Dao::Impl::CActiveCached::remove( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    int n = 0;
    makeQuery( cmp , cachedCmpNodes , query1 );
    n = cursor.select( query1 , dbCursorForUpdate );
    if( n == 0 )
    {
        return 0;
    }
    do
    {
        __registToTx( 
        stmt->getConnection()->getTransaction() , 
        *cursor.get() ,
        cdf::cached::ECachedUpdateModelDelete
        );
    }
    while( cursor.next() );
    cursor.removeAllSelected();
    return n;
}

int Dao::Impl::CActiveCached::getTotalCount()
{
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    return cursor.select( dbCursorViewOnly );
}

void Dao::Impl::CActiveCached::clear( cdf::CStatement* stmt )
{
    
    remove( cdf::dao::SeqCmpNode() , stmt );
}

void Dao::Impl::CActiveCached::load( cdf::CStatement* stmt )
{
    CActiveDaoImpl dao;
    cdf::dao::SQuery query;
    if ( !getNagtiveCheck().empty() )
    {
        cdf::dao::SCmpNode cmpNode;
        cmpNode.setColumnName( getNagtiveCheck() );
        cmpNode.setEqualType( cdf::dao::EQUAL_TYPE_NOT_EQUAL );
        bool canCheck = true;
        if ( getNagtiveCheck() == "id" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "type" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "name" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "status" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "start_dt" )
        {
            assert( false );
            canCheck = false;
        }
        else if ( getNagtiveCheck() == "end_dt" )
        {
            assert( false );
            canCheck = false;
        }
        else if ( getNagtiveCheck() == "loop_interval" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "start_date" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "end_date" )
        {
            cmpNode.setInt( 0 );
        }
        else if ( getNagtiveCheck() == "day_of_week" )
        {
            cmpNode.setString( "" );
        }
        else if ( getNagtiveCheck() == "js_str" )
        {
            cmpNode.setString( "" );
        }
        else 
        {
            assert( false );
            canCheck = false;
        }
        if ( canCheck )
        {
            query.cmpNodes.push_back( cmpNode );
        }
    }
    Message::DB::Tables::SeqTActive tables;
    TActiveCached table;
    dao.CActiveDaoImplBase::find( query , tables , stmt , false , false );
    Message::DB::Tables::SeqTActive::iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbAnyReference ref;
        table.__update( *iter );
        CCachedManager::instance()->getDb().insertRecord( 
        &TActiveCached::dbDescriptor , &ref , &table
        );
    }
}

void Dao::Impl::CActiveCached::flush( cdf::CStatement* stmt )
{
    CActiveDaoImpl dao;
    MEM_NODE_MAP flushMap;
    {
        cdf::CAutoLightLock l(_lock);
        if( _flushMap.size() == 0 )
        {
            return;
        }
        flushMap = _flushMap;
        _flushMap.clear();
    }
    for( MEM_NODE_MAP::const_iterator iter = flushMap.begin() ; iter != flushMap.end() ; iter ++ )
    {
        CDE_BEGIN_TRY
        {
            switch( iter->second->getUpdateMode() )
            {
                case ECachedUpdateModelAdd:
                {
                    dao.CActiveDaoImplBase::save( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelUpdate:
                {
                    dao.CActiveDaoImplBase::update( iter->second->getNode() , stmt , false );
                }
                break;
                case ECachedUpdateModelDelete:
                {
                    dao.CActiveDaoImplBase::remove( iter->second->getNode().id , stmt , false );
                }
            }
        }
        CDE_END_TRY( __FILE__ , __LINE__ );
    }
}

void Dao::Impl::CActiveCached::rollback( cdf::CTransaction* tx )
{
    cdf::CAutoLightLock l(_lock);
    TRANSACTION_MAP::iterator iter;
    iter = _transactionNodes.find( tx );
    if( _transactionNodes.end() == iter )
    {
        return;
    }
    for( 
    MEM_NODE_MAP::const_iterator iter1 = iter->second.begin() ;
    iter1 != iter->second.end() ; 
    iter1 ++ 
    )
    {
        if( iter1->second->getUpdateMode() & ECachedUpdateModelAdd )
        {
            iter1->second->setUpdateMode( ECachedUpdateModelDelete );
            MEM_NODE_MAP::iterator iter2 = _flushMap.find( iter1->first );
            if( iter2 == _flushMap.end() )
            {
                _flushMap[iter1->first] = iter1->second;
            }
            else
            {
                iter2->second = iter1->second;
            }
        }
    }
    _transactionNodes.erase( iter );
}

void Dao::Impl::CActiveCached::commit( cdf::CTransaction* tx )
{
    cdf::CAutoLightLock l(_lock);
    TRANSACTION_MAP::iterator iter;
    iter = _transactionNodes.find( tx );
    if( _transactionNodes.end() == iter )
    {
        return;
    }
    for( 
    MEM_NODE_MAP::const_iterator iter1 = iter->second.begin() ;
    iter1 != iter->second.end() ; 
    iter1 ++ )
    {
        MEM_NODE_MAP::iterator iter2 = _flushMap.find( iter1->first );
        if( iter1->second->getUpdateMode() & ECachedUpdateModelDelete )
        {
            iter1->second->setUpdateMode( ECachedUpdateModelDelete );
        }
        else if( iter1->second->getUpdateMode() & ECachedUpdateModelAdd )
        {
            if( !isInsertOnly() )
            {
                iter1->second->setUpdateMode( ECachedUpdateModelUpdate );
            }
            else
            {
                iter1->second->setUpdateMode( ECachedUpdateModelAdd );
            }
        }
        else if( iter1->second->getUpdateMode() & ECachedUpdateModelUpdate )
        {
            iter1->second->setUpdateMode( ECachedUpdateModelUpdate );
        }
        if( iter2 == _flushMap.end() )
        {
            _flushMap[iter1->first] = iter1->second;
        }
        else
        {
            iter2->second = iter1->second;
        }
    }
    _transactionNodes.erase( iter );
}

void Dao::Impl::CActiveCached::unnagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    CActiveDaoImpl dao;
    for( MEM_NODE_LIST::const_iterator iter = _nagtiveList.begin() ; iter != _nagtiveList.end() ; iter ++ )
    {
        dao.CActiveDaoImplBase::remove( (*iter)->getNode().id , stmt , false );
    }
    _nagtiveList.clear();
}
void Dao::Impl::CActiveCached::nagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( (int)_nagtiveList.size() <= ( getNagtiveCount() / 2 ) )
    {
        Message::DB::Tables::TActive t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CActiveDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CActiveDaoImplBase::save( t , stmt , false );
            nodePtr->getNode().__update( t );
            _nagtiveList.push_back( nodePtr );
        }
        if( !isBegin )
        {
            stmt->getConnection()->commit( false );
        }
    }
}
void Dao::Impl::CActiveCached::cached( const cdf::dao::SQuery& query , cdf::CStatement* stmt )
{
    CActiveDaoImpl dao;
    Message::DB::Tables::SeqTActive tables;
    dao.CActiveDaoImplBase::find( query , tables , stmt , false , false );
    cached( tables );
}
void Dao::Impl::CActiveCached::cached( Message::DB::Tables::SeqTActive& tables )
{
    TActiveCached table;
    Message::DB::Tables::SeqTActive::const_iterator iter;
    for( iter = tables.begin() ; iter != tables.end() ; iter ++ )
    {
        dbQuery q;
        q = "id=",(iter->id);
        dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
        if( cursor.select( q , dbCursorForUpdate ) == 0 )
        {
            dbAnyReference ref;
            table.__update( *iter );
            CCachedManager::instance()->getDb().insertRecord( &TActiveCached::dbDescriptor , &ref , &table );
        }
    }
}
void Dao::Impl::CActiveCached::evict( const cdf::dao::SeqCmpNode& cmp , cdf::CStatement* stmt )
{
    dbCursor< TActiveCached > cursor( &( CCachedManager::instance()->getDb() ) );
    dbQuery query1;
    cdf::cached::SeqCmpNode cachedCmpNodes;
    int n = 0;
    makeQuery( cmp , cachedCmpNodes , query1 );
    n = cursor.select( query1 , dbCursorForUpdate );
    if( n == 0 )
    {
        return;
    }
    cursor.removeAllSelected();
}
Dao::Impl::CActiveCached::MEM_NODE_PTR Dao::Impl::CActiveCached::getNagtive( cdf::CStatement* stmt )
{
    cdf::CAutoLightLock l( _nagtiveLock );
    if( _nagtiveList.empty() )
    {
        Message::DB::Tables::TActive t;
        t.__init();
        bool isBegin = stmt->getConnection()->getTransaction()->isBegin();
        if( !isBegin )
        {
            stmt->getConnection()->begin( false );
        }
        CActiveDaoImpl dao;
        while( (int)_nagtiveList.size() < getNagtiveCount() )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( ECachedUpdateModelAdd );
            dao.CActiveDaoImplBase::save( t , stmt , false );
            nodePtr->getNode().__update( t );
            _nagtiveList.push_back( nodePtr );
        }
        if( !isBegin )
        {
            stmt->getConnection()->commit( false );
        }
    }
    if( _nagtiveList.empty() )
    {
        return NULL;
    }
    else
    {
        MEM_NODE_PTR node = *_nagtiveList.begin();
        _nagtiveList.pop_front();
        return node;
    }
}
void Dao::Impl::CActiveCached::__registToTx( 
	cdf::CTransaction* tx , 
	const TActiveCached& table,
	cdf::cached::ECachedUpdateModel model
	)
{
    cdf::CAutoLightLock l(_lock);
    if( tx->isBegin() && !isInsertOnly() )
    {
        CCachedTransaction *tx1 = (CCachedTransaction*)tx;
        tx1->insertTable( this );
        TRANSACTION_MAP::iterator iter;
        iter = _transactionNodes.find( tx );
        if( _transactionNodes.end() == iter )
        {
            MEM_NODE_PTR nodePtr = new MEM_NODE();
            nodePtr->setUpdateMode( model );
            Message::DB::Tables::TActive v;
            table.__save( v );
            nodePtr->setNode( v );
            _transactionNodes[tx][nodePtr->getNode().id] = nodePtr;
        }
        else
        {
            MEM_NODE_MAP::iterator iter2 = iter->second.find( table.id );
            if( iter2 == iter->second.end() )
            {
                MEM_NODE_PTR nodePtr = new MEM_NODE();
                nodePtr->setUpdateMode( model );
                Message::DB::Tables::TActive v;
                table.__save( v );
                nodePtr->setNode( v );
                iter->second[ table.id ] = nodePtr;
            }
            else
            {
                iter2->second->setUpdateMode( iter2->second->getUpdateMode() | model );
                table.__save( iter2->second->getNode() );
            }
        }
    }
    else
    {
        MEM_NODE_PTR nodePtr = new MEM_NODE();
        if( model == ECachedUpdateModelAdd && !isInsertOnly() )
        {
            nodePtr->setUpdateMode( ECachedUpdateModelUpdate );
        }
        else
        {
            nodePtr->setUpdateMode( model );
        }
        Message::DB::Tables::TActive v;
        table.__save( v );
        nodePtr->setNode( v );
        MEM_NODE_MAP::iterator iter = _flushMap.find( table.id );
        if( iter == _flushMap.end() )
        {
            _flushMap[table.id] = nodePtr;
        }
        else
        {
            iter->second = nodePtr;
        }
    }
}
void Dao::Impl::CActiveCached::__update(
    TActiveCached& v,
	const cdf::dao::SeqDataNode& seq 
	)
{
    cdf::dao::SeqDataNode::const_iterator iter;
    for( iter = seq.begin() ; iter != seq.end() ; iter ++ )
    {
        if( iter->getColumnName() == "type" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.type = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "name" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.name = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "status" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.status = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "start_dt" )
        {
            if( iter->getDataType() != cdf::TYPE_DATE )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            cdf::CDateTime date( iter->getDate() );
            date.clearMillSecond();
            v.startDt = date.getTotalMill();
            continue;
        }
        if( iter->getColumnName() == "end_dt" )
        {
            if( iter->getDataType() != cdf::TYPE_DATE )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            cdf::CDateTime date( iter->getDate() );
            date.clearMillSecond();
            v.endDt = date.getTotalMill();
            continue;
        }
        if( iter->getColumnName() == "loop_interval" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.loopInterval = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "start_date" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.startDate = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "end_date" )
        {
            if( iter->getDataType() != cdf::TYPE_INT )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.endDate = iter->getInt();
            continue;
        }
        if( iter->getColumnName() == "day_of_week" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.dayOfWeek = iter->getString();
            continue;
        }
        if( iter->getColumnName() == "js_str" )
        {
            if( iter->getDataType() != cdf::TYPE_STRING )
            {
                std::string exp = "table name:t_active column name:" + iter->getColumnName() + " type error";
                throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
            }
            v.jsStr = iter->getString();
            continue;
        }
        std::string exp = "table name:t_active column name:" + iter->getColumnName() + " error";
        throw cdf::CException( exp.c_str() , cdf::ExceptionCodeDB );
    }
}