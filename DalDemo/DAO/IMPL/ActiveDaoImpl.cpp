#include "Dao/Impl/ActiveDaoImpl.h"
Dao::Impl::CActiveDaoImpl::CActiveDaoImpl()
{
}
Dao::Impl::CActiveDaoImpl::~CActiveDaoImpl()
{
}

void Dao::Impl::CActiveDaoImpl::load(Message::DB::Tables::SeqTActive& tActives)
{
	cdf::dao::SQuery query;
	//cdf::dao::SCmpNode cmpNode;

	//cmpNode.setColumnName(_id);
	//cmpNode.setEqualType(cdf::dao::EQUAL_TYPE_GRANTER_EQUAL);
	//cmpNode.setInt(0);
	//query.cmpNodes.push_back(cmpNode);
	find(query, tActives);
}