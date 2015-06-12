#include "Dao/Base/ActiveDaoBase.h"
Dao::IActiveDaoBase::IActiveDaoBase()
{
}
Dao::IActiveDaoBase::~IActiveDaoBase()
{
}

const std::string Dao::IActiveDaoBase::_tableName = "t_active";
const std::string Dao::IActiveDaoBase::_id = "id";
const std::string Dao::IActiveDaoBase::_type = "type";
const std::string Dao::IActiveDaoBase::_name = "name";
const std::string Dao::IActiveDaoBase::_status = "status";
const std::string Dao::IActiveDaoBase::_startDt = "start_dt";
const std::string Dao::IActiveDaoBase::_endDt = "end_dt";
const std::string Dao::IActiveDaoBase::_loopInterval = "loop_interval";
const std::string Dao::IActiveDaoBase::_startDate = "start_date";
const std::string Dao::IActiveDaoBase::_endDate = "end_date";
const std::string Dao::IActiveDaoBase::_dayOfWeek = "day_of_week";
const std::string Dao::IActiveDaoBase::_jsStr = "js_str";