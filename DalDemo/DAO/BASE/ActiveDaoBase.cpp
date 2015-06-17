#include "ActiveDaoBase.h"

DAO::IActiveDaoBase::IActiveDaoBase()
{
}
DAO::IActiveDaoBase::~IActiveDaoBase()
{
}

const std::string DAO::IActiveDaoBase::_tableName = "t_active";
const std::string DAO::IActiveDaoBase::_id = "id";
const std::string DAO::IActiveDaoBase::_type = "type";
const std::string DAO::IActiveDaoBase::_name = "name";
const std::string DAO::IActiveDaoBase::_status = "status";
const std::string DAO::IActiveDaoBase::_startDt = "start_dt";
const std::string DAO::IActiveDaoBase::_endDt = "end_dt";
const std::string DAO::IActiveDaoBase::_loopInterval = "loop_interval";
const std::string DAO::IActiveDaoBase::_startDate = "start_date";
const std::string DAO::IActiveDaoBase::_endDate = "end_date";
const std::string DAO::IActiveDaoBase::_dayOfWeek = "day_of_week";
const std::string DAO::IActiveDaoBase::_jsStr = "js_str";