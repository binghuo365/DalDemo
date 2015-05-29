#ifndef _DAFRAME_DAO_DASE_H_
#define _DAFRAME_DAO_DASE_H_

#include "daoquerydef.h"
#include "publicdef.h"

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
				CStatement* stmt 
				);

			void writeStmt( 
				int index ,
				const SDataNode& dateNode , 
				CStatement* stmt 
				);

			void writeStmt( 
				int startIndex ,
				const SeqDataNode& seqDataNode , 
				CStatement* stmt 
				);

			ulong64_t executeSql(
				const std::string& sql
				);

			ulong64_t executeSql(
				const std::string& sql ,
				CStatement* stmt
				);
		};
	}
}
#endif
