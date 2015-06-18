#include "winsock2.h"
#include "DAFrame/DAOBASE/connectionmanager.h"
#include "DAFrame/DAOBASE/poolconnectionmanager.h"
#include "DAFrame/MYSQLIMPL/mysqlconnection.h"
#include "DAFrame/DAOBASE/poolconnautoptr.h"
#include "DAFrame/DAOBASE/statement.h"
#include "DAFrame/DAOBASE/resultset.h"
#include "DAO/TActive.h"
#include "Dao/Impl/ActiveDaoImpl.h"
#include <iostream>

int main(int argc, char* argv[])
{
	DAFrame::CConnectionManager::registProtocol("mysql", new DAFrame::mysql::CMySQLConnection);
	DAFrame::CPoolConnectionManager::initialize("mysql://192.168.9.82:3306/gw_power", 50, "root", "root");
	DAO::Tables::SeqTActive tables;
	DAO::IActiveDao* activeDao = new DAO::IMPL::CActiveDaoImpl();
	activeDao->load(tables);
	for (DAO::Tables::SeqTActive::iterator it = tables.begin(); it != tables.end(); ++it)
	{
		std::cout << "id:" << it->id << ", name: " << it->name << ", startDt: " << it->startDt.asString() << std::endl;
	}
	return 0;
}

