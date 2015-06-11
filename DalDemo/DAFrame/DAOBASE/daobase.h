#ifndef _DAFRAME_DAO_DASE_H_
#define _DAFRAME_DAO_DASE_H_

#include "daoquerydef.h"
#include "publicdef.h"
#include "statement.h"

namespace DAFrame
{
	namespace DAO
	{
		class CDaoBase
		{
		public:
			CDaoBase();
			virtual ~CDaoBase();

			std::string makeUpdate(
				const SeqDataNode& seqDataNode
				);

			std::string makeQuery(
				const SeqCmpNode& seqCmpNode
				);

			std::string makeOrder(
				const SQuery& query
				);

			void writeStmt( 
				int startIndex ,
				const SeqCmpNode& seqCmpNode , 
				DAFrame::CStatement* stmt
				);

			void writeStmt( 
				int index ,
				const SDataNode& dateNode , 
				DAFrame::CStatement* stmt
				);

			void writeStmt( 
				int startIndex ,
				const SeqDataNode& seqDataNode , 
				DAFrame::CStatement* stmt
				);

			ulong64_t executeSql(
				const std::string& sql
				);

			ulong64_t executeSql(
				const std::string& sql ,
				DAFrame::CStatement* stmt
				);
		};
	}
}
#endif
