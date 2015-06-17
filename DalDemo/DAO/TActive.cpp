#include "TActive.h"

DAO::Tables::TActive::TActive()
{
    __init();
}

bool
DAO::Tables::TActive::operator==(const TActive& __rhs) const
{
    return !operator!=(__rhs);
}

bool
DAO::Tables::TActive::operator!=(const TActive& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(id != __rhs.id)
    {
        return true;
    }
    if(type != __rhs.type)
    {
        return true;
    }
    if(name != __rhs.name)
    {
        return true;
    }
    if(status != __rhs.status)
    {
        return true;
    }
    if(startDt != __rhs.startDt)
    {
        return true;
    }
    if(endDt != __rhs.endDt)
    {
        return true;
    }
    if(loopInterval != __rhs.loopInterval)
    {
        return true;
    }
    if(startDate != __rhs.startDate)
    {
        return true;
    }
    if(endDate != __rhs.endDate)
    {
        return true;
    }
    if(dayOfWeek != __rhs.dayOfWeek)
    {
        return true;
    }
    if(jsStr != __rhs.jsStr)
    {
        return true;
    }
    return false;
}

bool
DAO::Tables::TActive::operator<(const TActive& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(id < __rhs.id)
    {
        return true;
    }
    else if(__rhs.id < id)
    {
        return false;
    }
    if(type < __rhs.type)
    {
        return true;
    }
    else if(__rhs.type < type)
    {
        return false;
    }
    if(name < __rhs.name)
    {
        return true;
    }
    else if(__rhs.name < name)
    {
        return false;
    }
    if(status < __rhs.status)
    {
        return true;
    }
    else if(__rhs.status < status)
    {
        return false;
    }
    if(startDt < __rhs.startDt)
    {
        return true;
    }
    else if(__rhs.startDt < startDt)
    {
        return false;
    }
    if(endDt < __rhs.endDt)
    {
        return true;
    }
    else if(__rhs.endDt < endDt)
    {
        return false;
    }
    if(loopInterval < __rhs.loopInterval)
    {
        return true;
    }
    else if(__rhs.loopInterval < loopInterval)
    {
        return false;
    }
    if(startDate < __rhs.startDate)
    {
        return true;
    }
    else if(__rhs.startDate < startDate)
    {
        return false;
    }
    if(endDate < __rhs.endDate)
    {
        return true;
    }
    else if(__rhs.endDate < endDate)
    {
        return false;
    }
    if(dayOfWeek < __rhs.dayOfWeek)
    {
        return true;
    }
    else if(__rhs.dayOfWeek < dayOfWeek)
    {
        return false;
    }
    if(jsStr < __rhs.jsStr)
    {
        return true;
    }
    else if(__rhs.jsStr < jsStr)
    {
        return false;
    }
    return false;
}

void
DAO::Tables::TActive::__init()
{
    id = 0;
    type = 0;
    status = 0;
    loopInterval = 0;
    startDate = 0;
    endDate = 0;
}

void
DAO::Tables::TActive::__update(const TActive& __rhs)
{
    id = __rhs.id;
    type = __rhs.type;
    if( name != __rhs.name ) 
    {
        name = __rhs.name;
    }
    status = __rhs.status;
    startDt = __rhs.startDt;
    endDt = __rhs.endDt;
    loopInterval = __rhs.loopInterval;
    startDate = __rhs.startDate;
    endDate = __rhs.endDate;
    if( dayOfWeek != __rhs.dayOfWeek ) 
    {
        dayOfWeek = __rhs.dayOfWeek;
    }
    if( jsStr != __rhs.jsStr ) 
    {
        jsStr = __rhs.jsStr;
    }
}
