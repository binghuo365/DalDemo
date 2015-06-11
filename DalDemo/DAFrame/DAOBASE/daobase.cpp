#include "daobase.h"
#include "typetransform.h"
#include "statement.h"

using namespace DAFrame;
using namespace DAO;

CDaoBase::CDaoBase()
{
}

CDaoBase::~CDaoBase()
{
}

std::string CDaoBase::makeUpdate(
	const SeqDataNode& seqDataNode
	)
{
	if (seqDataNode.size() <= 0)
	{
		return "";
	}
	std::string sql;
	sql += " set";
	for (SeqDataNode::const_iterator iter = seqDataNode.begin(); iter != seqDataNode.end(); iter++)
	{
		sql += " ";
		sql += iter->getColumnName();
		sql += " = ? , ";
	}
	if (seqDataNode.size() > 0)
	{
		sql.erase(sql.size() - 2, 2);
	}
	return sql;
}

std::string CDaoBase::makeQuery(
	const SeqCmpNode& seqCmpNode
	)
{
	if (seqCmpNode.size() <= 0)
	{
		return "";
	}
	std::string sql;
	sql += " where";
	for (SeqCmpNode::const_iterator iter = seqCmpNode.begin(); iter != seqCmpNode.end(); iter++)
	{
		sql += " ";
		if (iter->isSet())
		{
			sql += iter->getColumnName();
			sql += " in ( ";
			if (iter->getDataType() == TYPE_INT)
			{
				std::vector<int>::const_iterator iter1;
				for (iter1 = iter->getIntSet().begin(); iter1 != iter->getIntSet().end(); iter1++)
				{
					sql += ToStr(*iter1);
					sql += ",";
				}
			}
			else if (iter->getDataType() == TYPE_LONG64)
			{
				std::vector<long64_t>::const_iterator iter1;
				for (iter1 = iter->getLong64Set().begin(); iter1 != iter->getLong64Set().end(); iter1++)
				{
					sql += ToStr(*iter1);
					sql += ",";
				}
			}
			sql.erase(sql.length() - 1, 1);
			sql += " ) and ";
			continue;
		}
		if (iter->getDataType() == TYPE_STRING)
		{
			if (iter->getLikeCmpType() == CMP_LIKE_TYPE_LIKE)
			{
				sql += iter->getColumnName();
				sql += " like '%" +
					//CStrFun::filter_str(iter->getString().c_str(), "'")
					iter->getString()
					+ "%'";
				sql += " and ";
				continue;
			}
			else if (iter->getCaseCmp() == CMP_TYPE_I_CASE)
			{
				sql += CDF_BINARY_CMP;
				sql += " ";
			}
		}
		sql += iter->getColumnName();
		sql += " ";
		EQUAL_TYPE equalType = iter->getEqualType();
		if (equalType & EQUAL_TYPE_LESS)
		{
			sql += "<";
		}
		if (equalType & EQUAL_TYPE_GRANTER)
		{
			sql += ">";
		}
		if (equalType & EQUAL_TYPE_EQUAL)
		{
			sql += "=";
		}
		sql += "? and ";
	}
	if (seqCmpNode.size() > 0)
	{
		sql.erase(sql.size() - 4, 4);
	}
	return sql;
}

std::string CDaoBase::makeOrder(
	const SQuery& query
	)
{
	std::string sql;
	if (query.orderType.size() > 0)
	{
		sql += " order by";
		for (SeqOrderType::const_iterator iter = query.orderType.begin();
			iter != query.orderType.end();
			iter++)
		{
			sql += " ";
			sql += iter->columnName;
			switch (iter->type)
			{
			case ORDER_TYPE_ASC:
				sql += " asc,";
				break;
			case ORDER_TYPE_DESC:
				sql += " desc,";
				break;
			}
		}
		sql.erase(sql.size() - 1);
	}
	if (query.startIndex < query.endIndex)
	{
		sql += " limit ";
		sql += ToStr(query.startIndex);
		sql += " , ";
		sql += ToStr(query.endIndex - query.startIndex);
	}
	return sql;
}

void CDaoBase::writeStmt(
	int index,
	const SDataNode& dataNode,
	DAFrame::CStatement* stmt
	)
{
	switch (dataNode.getDataType())
	{
	case TYPE_INT:
		stmt->setInt(index, dataNode.getInt());
		break;
	case TYPE_DOUBLE:
		stmt->setDouble(index, dataNode.getDouble());
		break;
	case TYPE_LONG64:
		stmt->setLong64(index, dataNode.getLong64());
		break;
	case TYPE_STRING:
		stmt->setString(index, dataNode.getString());
		break;
	case TYPE_DATE:
		stmt->setDate(index, dataNode.getDate());
		break;
	}
}

void CDaoBase::writeStmt(
	int startIndex,
	const SeqCmpNode& seqCmpNode,
	DAFrame::CStatement* stmt
	)
{
	for (SeqCmpNode::const_iterator iter = seqCmpNode.begin(); iter != seqCmpNode.end(); iter++)
	{
		const SCmpNode& cmpNode = *iter;
		if (cmpNode.isSet())
		{
			continue;
		}
		if (!(cmpNode.getDataType() == TYPE_STRING &&
			cmpNode.getLikeCmpType() == CMP_LIKE_TYPE_LIKE))
		{
			writeStmt(startIndex++, cmpNode, stmt);
		}
	}
}

void CDaoBase::writeStmt(
	int startIndex,
	const SeqDataNode& seqDataNode,
	DAFrame::CStatement* stmt
	)
{
	for (SeqDataNode::const_iterator iter = seqDataNode.begin(); iter != seqDataNode.end(); iter++)
	{
		const SDataNode& dataNode = *iter;
		writeStmt(startIndex++, dataNode, stmt);
	}
}

ulong64_t DAFrame::DAO::CDaoBase::executeSql(const std::string& sql)
{
	//DAO::CPoolConnAutoPtr<CPoolConnection> conn = CPoolConnectionManager::getConnection();
	//std::auto_ptr<DAFrame::CStatement> stmt = conn->createStatement();
	return 0;
}

ulong64_t DAFrame::DAO::CDaoBase::executeSql(const std::string& sql, DAFrame::CStatement* stmt)
{
	return stmt->executeUpdate(sql.c_str());
}
