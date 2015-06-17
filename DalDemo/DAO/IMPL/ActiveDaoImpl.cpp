#include "ActiveDaoImpl.h"
DAO::IMPL::CActiveDaoImpl::CActiveDaoImpl()
{
}
DAO::IMPL::CActiveDaoImpl::~CActiveDaoImpl()
{
}

void DAO::IMPL::CActiveDaoImpl::load(DAO::Tables::SeqTActive& tActives)
{
	DAFrame::DAO::SQuery query;
	DAFrame::DAO::SCmpNode cmpNode;

	cmpNode.setColumnName(_id);
	cmpNode.setEqualType(DAFrame::DAO::EQUAL_TYPE_GRANTER_EQUAL);
	cmpNode.setInt(0);
	query.cmpNodes.push_back(cmpNode);
	find(query, tActives);
}