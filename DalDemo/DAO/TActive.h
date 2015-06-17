#ifndef ___TActive_h__
#define ___TActive_h__

#include "vector"
#include "map"
#include "string"
#include "algorithm"
#include "..\DAFrame\DAOBASE\datetime.h"
 
namespace DAO
{
	namespace Tables
	{
		struct TActive
		{
			int id;
			int type;
			std::string name;
			int status;
			DAFrame::CDateTime startDt;
			DAFrame::CDateTime endDt;
			int loopInterval;
			int startDate;
			int endDate;
			std::string dayOfWeek;
			std::string jsStr;

			TActive();
			void __init();
			void __update(const TActive&);
			bool operator==(const TActive&) const;
			bool operator!=(const TActive&) const;
			bool operator<(const TActive&) const;
		};

		typedef std::vector<DAO::Tables::TActive> SeqTActive;
	}
}

#endif
