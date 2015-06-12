// **********************************************************************
//
// Copyright (c) 2003-2009 CDE, Inc. All rights reserved.
//
// This copy of Cde is licensed to you under the terms described in the
// CDE_LICENSE file included in this distribution.
//
// **********************************************************************

// Cde version 1.0.1
// Generated from file `TActive.cdl'
#include "TActive.h"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

Message::DB::Tables::TActive::TActive()
{
    __init();
}

bool
Message::DB::Tables::TActive::operator==(const TActive& __rhs) const
{
    return !operator!=(__rhs);
}

bool
Message::DB::Tables::TActive::operator!=(const TActive& __rhs) const
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
Message::DB::Tables::TActive::operator<(const TActive& __rhs) const
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
Message::DB::Tables::TActive::__init()
{
    id = 0;
    type = 0;
    status = 0;
    loopInterval = 0;
    startDate = 0;
    endDate = 0;
}

void
Message::DB::Tables::TActive::__write(cdf::CSerializeStream& __os) const
{
    __os.write(id);
    __os.write(type);
    __os.write(name);
    __os.write(status);
    __os.write(startDt);
    __os.write(endDt);
    __os.write(loopInterval);
    __os.write(startDate);
    __os.write(endDate);
    __os.write(dayOfWeek);
    __os.write(jsStr);
}

void
Message::DB::Tables::TActive::__read(cdf::CSerializeStream& __is)
{
    __is.read(id);
    __is.read(type);
    __is.read(name);
    __is.read(status);
    __is.read(startDt);
    __is.read(endDt);
    __is.read(loopInterval);
    __is.read(startDate);
    __is.read(endDate);
    __is.read(dayOfWeek);
    __is.read(jsStr);
}

void
Message::DB::Tables::TActive::__update(const TActive& __rhs)
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

void
Message::DB::Tables::__write(cdf::CSerializeStream& __os, const ::Message::DB::Tables::SeqTActive& v, ::Message::DB::Tables::__U__SeqTActive)
{
    __os.writeSize(int(v.size()));
    ::Message::DB::Tables::SeqTActive::const_iterator p;
    for(p = v.begin(); p != v.end(); ++p)
    {
        (*p).__write(__os);
    }
}

void
Message::DB::Tables::__read(cdf::CSerializeStream& __is, ::Message::DB::Tables::SeqTActive& v, ::Message::DB::Tables::__U__SeqTActive)
{
    int sz;
    __is.readSize(sz);
    __is.startSeq(sz, 35);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is.checkSeq();
        __is.endElement();
    }
    __is.endSeq(sz);
}
