#include "daoquerydef.h"
#include "sqlexception.h"

#define VALID_NODE_TYPE( NODE_TYPE ) \
	if ( NODE_TYPE != _dataType ) \
	throw std::exception("Data Type Error");

using namespace DAFrame::DAO;
using namespace DAFrame;

SDataNode::SDataNode()
:_columnName("") ,
_dataType( DAFrame::TYPE_INT ) ,
_int( 0 ) ,
_double( 0.0 ),
_long64( 0 ) ,
_isSet( false )
{
}

SDataNode::SDataNode( const SDataNode& node )
:_columnName( node._columnName ) ,
_dataType( node._dataType ) ,
_int( node._int ) ,
_double( node._double ),
_long64( node._long64 ) ,
_string( node._string ) ,
_date( node._date ) ,
_isSet( node._isSet )
{
}

SDataNode::~SDataNode()
{
}

void SDataNode::setColumnName( const std::string& columnName )
{
	_columnName = columnName;
}
const std::string& SDataNode::getColumnName() const
{
	if( _columnName.length() == 0 )
	{
		throw CSQLException(ERROR_NOT_HAVE_COLUMN,"Column name will not be null"); 
	}
	return _columnName;
}

EDATATYPE SDataNode::getDataType() const
{
	return _dataType;
}

void SDataNode::setInt( int v )
{
	_isSet = false;
	_dataType = TYPE_INT;
	_int = v;
}
const int& SDataNode::getInt() const
{
	VALID_NODE_TYPE(TYPE_INT);
	return _int;
}

void SDataNode::setDouble( double v )
{
	_isSet = false;
	_dataType = TYPE_DOUBLE;
	_double = v;
}

const double& SDataNode::getDouble() const
{
	VALID_NODE_TYPE(TYPE_DOUBLE);
	return _double;
}

void SDataNode::setLong64( long64_t v )
{
	_isSet = false;
	_dataType = TYPE_LONG64;
	_long64 = v;
}
const long64_t& SDataNode::getLong64() const
{
	VALID_NODE_TYPE(TYPE_LONG64);
	return _long64;
}

void SDataNode::setString( const std::string& v )
{
	_isSet = false;
	_dataType = TYPE_STRING;
	_string = v;
}
const std::string& SDataNode::getString() const
{
	VALID_NODE_TYPE(TYPE_STRING);
	return _string;
}

void SDataNode::setDate(const CDateTime& v)
{
	_isSet = false;
	_dataType = TYPE_DATE;
	_date = v;
}
const CDateTime& SDataNode::getDate() const
{
	VALID_NODE_TYPE(TYPE_DATE);
	return _date;
}

bool SDataNode::operator < ( const SDataNode& node ) const
{
	switch( _dataType )
	{
	case TYPE_INT:
		return _int < node._int;
		break;
	case TYPE_STRING:
		return _string < node._string;
		break;
	case TYPE_DATE:
		return _date < node._date;
		break;
	case TYPE_LONG64:
		return _long64 < node._long64;
		break;
	case TYPE_DOUBLE:
		return _double < node._double;
		break;
	}
	return false;
}

bool SDataNode::isSet() const
{
	return _isSet;
}

SCmpNode::SCmpNode()
:_equalType( EQUAL_TYPE_EQUAL ) ,
_caseCmp( CMP_TYPE_I_CASE ),
_likeCmp( CMP_LIKE_TYPE_UNLIKE )
{
}

SCmpNode::~SCmpNode()
{
}

SCmpNode::SCmpNode( const SCmpNode& daoNode )
:SDataNode( daoNode ),
_equalType( daoNode._equalType ),
_caseCmp( daoNode._caseCmp ) ,
_likeCmp( daoNode._likeCmp ) ,
_intSet( daoNode._intSet ) ,
_long64Set( daoNode._long64Set ) 
{
}


void SCmpNode::setEqualType( EQUAL_TYPE equalType )
{
	if( ( equalType & EQUAL_TYPE_LESS ) &&
		( equalType & EQUAL_TYPE_GRANTER ) && 
		( equalType & EQUAL_TYPE_EQUAL ) )
	{
		throw CSQLException(ERROR_DATABASE_UNSUPPORT,"unsupport equaltype less && granter && equal");
	}
	_equalType = equalType;
	_likeCmp = CMP_LIKE_TYPE_UNLIKE;
}

void SCmpNode::setCaseCmp( CMP_TYPE caseCmp )
{
	_caseCmp = caseCmp;
}

CMP_TYPE SCmpNode::getCaseCmp() const
{
	return _caseCmp;
}

void SCmpNode::setLikeCmpType( CMP_LIKE_TYPE likeType )
{
	_likeCmp = likeType;
}

CMP_LIKE_TYPE SCmpNode::getLikeCmpType() const
{
	return _likeCmp;
}

EQUAL_TYPE SCmpNode::getEqualType() const
{
	return _equalType;
}

void SCmpNode::setIntSet( const std::vector<int>& intSet )
{
	_dataType = TYPE_INT;
	_isSet = true;
	_intSet = intSet;
}

const std::vector<int>& SCmpNode::getIntSet() const
{
	VALID_NODE_TYPE(TYPE_INT);
	return _intSet;
}

void SCmpNode::setLong64Set( const std::vector<long64_t>& long64Set )
{
	_dataType = TYPE_LONG64;
	_isSet = true;
	_long64Set = long64Set;
}

const std::vector<long64_t>& SCmpNode::getLong64Set() const
{
	VALID_NODE_TYPE(TYPE_LONG64);
	return _long64Set;
}

SOrderNode::SOrderNode()
:_orderType(ORDER_TYPE_DESC)
{

}
SOrderNode::~SOrderNode()
{
}

SOrderNode::SOrderNode( const SOrderNode& node )
:SDataNode( node ),_orderType( node._orderType )
{
}

bool SOrderNode::operator < ( const SOrderNode& node ) const
{
	if( _orderType == ORDER_TYPE_ASC )
	{
		return SDataNode::operator < ( node );
	}
	else
	{
		return node.SDataNode::operator < ( *this );
	}
}

SOrderType::SOrderType( const std::string& columnNameV , ORDER_TYPE typeV )
:columnName( columnNameV ) , type( typeV )
{
}

SOrderType::SOrderType( const SOrderType& orderType )
:columnName( orderType.columnName ) , type( orderType.type )
{
}

SQuery::SQuery( int startIndexV , int endIndexV , FIND_COUNT_TYPE countTypeV)
:startIndex(startIndexV),endIndex(endIndexV),countType( countTypeV )
{
}

SQuery::SQuery()
:startIndex(0),endIndex(0),countType(FIND_COUNT_TYPE_WITH_DATA)
{
}

SQuery::SQuery( const SQuery& findType )
:cmpNodes(findType.cmpNodes),
orderType(findType.orderType),
countType(findType.countType),
startIndex(findType.startIndex),
endIndex(findType.endIndex)
{
}
