#include "DAFrame/DAOBASE/connectionmanager.h"
#include "DAFrame/DAOBASE/poolconnectionmanager.h"

int main(int argc, char* argv[])
{
	DAFrame::CConnectionManager::registProtocol("mysql", NULL);
	DAFrame::CPoolConnectionManager::initialize("mysql://192.168.9.82:3306/gw_power", 50, "root", "root");
	DAFrame::CPoolConnAutoPtr<DAFrame::CPoolConnection> conn
		= DAFrame::CPoolConnectionManager::getConnection();
	return 0;
}

