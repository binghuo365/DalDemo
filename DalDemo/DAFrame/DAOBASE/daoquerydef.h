#ifndef _CDF_DAO_QUERY_DEF_H_
#define _CDF_DAO_QUERY_DEF_H_

#include <string>
#include <vector>
#include <memory>
#include "publicdef.h"
#include "datetime.h"

namespace DAFrame
{
	namespace DAO
	{
		enum EQUAL_TYPE
		{
			EQUAL_TYPE_EQUAL = 0x01,
			EQUAL_TYPE_LESS = 0x02,
			EQUAL_TYPE_GRANTER = 0x04,
			EQUAL_TYPE_NOT_EQUAL = EQUAL_TYPE_LESS | EQUAL_TYPE_GRANTER,
			EQUAL_TYPE_LESS_EQUAL = EQUAL_TYPE_LESS | EQUAL_TYPE_EQUAL,
			EQUAL_TYPE_GRANTER_EQUAL = EQUAL_TYPE_GRANTER | EQUAL_TYPE_EQUAL,
		};

		enum ORDER_TYPE
		{
			ORDER_TYPE_ASC,
			ORDER_TYPE_DESC
		};

		enum CMP_TYPE
		{
			CMP_TYPE_CASE,    //大小不敏感
			CMP_TYPE_I_CASE   //大小写敏感
		};

		enum CMP_LIKE_TYPE
		{
			CMP_LIKE_TYPE_LIKE,
			CMP_LIKE_TYPE_UNLIKE
		};

		enum FIND_COUNT_TYPE
		{
			FIND_COUNT_TYPE_WITH_COUNT = 0x01,
			FIND_COUNT_TYPE_WITH_DATA= 0x02, 
			FIND_COUNT_TYPE_COUNT_DATA = 
				FIND_COUNT_TYPE_WITH_COUNT | FIND_COUNT_TYPE_WITH_DATA,
		};

		class SDataNode
		{
		public:

			SDataNode();
			SDataNode( const SDataNode& daoNode );
			virtual ~SDataNode();

			void setColumnName( const std::string& columnName );
			const std::string& getColumnName() const;
			EDATATYPE getDataType() const;

			void setInt( int v );
			const int& getInt( ) const;

			void setDouble( double v );
			const double& getDouble( ) const;

			void setLong64( long64_t v );
			const long64_t& getLong64() const;

			void setString( const std::string& v );
			const std::string& getString() const;

			void setDate(const CDateTime& v);
			const CDateTime& getDate() const;

			bool isSet() const;

			bool operator < ( const SDataNode& node ) const;
		
		protected:
			std::string _columnName;
			EDATATYPE _dataType;
			bool _isSet;
			int _int;
			double _double;
			long64_t _long64;
			std::string _string;
			CDateTime _date;
		};
		typedef std::vector<SDataNode> SeqDataNode;

		class SCmpNode
			:public SDataNode
		{
		public:

			SCmpNode();
			virtual ~SCmpNode();
			SCmpNode( const SCmpNode& daoNode );

			void setCaseCmp( CMP_TYPE caseCmp );
			CMP_TYPE getCaseCmp() const;

			void setEqualType( EQUAL_TYPE equalType );
			EQUAL_TYPE getEqualType() const;

			void setLikeCmpType( CMP_LIKE_TYPE likeType );
			CMP_LIKE_TYPE getLikeCmpType() const;

			void setIntSet( const std::vector<int>& intSet );
			const std::vector<int>& getIntSet() const;

			void setLong64Set( const std::vector<long64_t>& long64Set );
			const std::vector<long64_t>& getLong64Set() const;

		 protected:
			EQUAL_TYPE _equalType;
			CMP_TYPE _caseCmp;
			CMP_LIKE_TYPE _likeCmp;
			std::vector<int> _intSet;
			std::vector<long64_t> _long64Set;
		};
		typedef std::vector<SCmpNode> SeqCmpNode;

		class SOrderNode
			:public SDataNode
		{
		public:
			SOrderNode();
			virtual ~SOrderNode();
			SOrderNode( const SOrderNode& daoNode );

			bool operator < ( const SOrderNode& node ) const;

		public:
			ORDER_TYPE _orderType;
		};
		typedef std::vector<SOrderNode> SeqOrderNode;
	

		struct SOrderType
		{
			SOrderType( const std::string& columnNameV , ORDER_TYPE typeV = ORDER_TYPE_DESC );
			SOrderType( const SOrderType& orderType );
			std::string columnName;
			ORDER_TYPE type;
		};

		typedef std::vector<SOrderType> SeqOrderType; 

		struct SQuery
		{
		public:
			SQuery( 
				int startIndex , 
				int endIndex , 
				FIND_COUNT_TYPE countType = FIND_COUNT_TYPE_WITH_DATA 
				);
			SQuery();
			SQuery( const SQuery& findType );
			SeqCmpNode cmpNodes;
			SeqOrderType orderType;
			FIND_COUNT_TYPE countType;
			int startIndex; //start with 0
			int endIndex;
		};
	}
}
#endif
