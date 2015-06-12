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

#ifndef ___TActive_h__
#define ___TActive_h__

#include "vector"
#include "map"
#include "string"
#include "algorithm"

#ifdef CDE_INT_VERSION
#   if CDE_INT_VERSION / 100 != 100
#       error Cde version mismatch!
#   endif
#   if CDE_INT_VERSION % 100 < 1
#       error Cde patch level mismatch!
#   endif
#endif

namespace Message
{
    namespace DB
    {
        namespace Tables
        {
            struct TActive
            {
                int id;
                int type;
                std::string name;
                int status;
                cdf::CDateTime startDt;
                cdf::CDateTime endDt;
                int loopInterval;
                int startDate;
                int endDate;
                std::string dayOfWeek;
                std::string jsStr;

                TActive();
                bool operator==(const TActive&) const;
                bool operator!=(const TActive&) const;
                bool operator<(const TActive&) const;
                
                void __init();
                void __write(cdf::CSerializeStream&) const;
                void __read(cdf::CSerializeStream&);
                void __update(const TActive&);
            };

            typedef std::vector< ::Message::DB::Tables::TActive> SeqTActive;

            class __U__SeqTActive { };
            void __write(cdf::CSerializeStream&, const SeqTActive&, __U__SeqTActive);
            void __read(cdf::CSerializeStream&, SeqTActive&, __U__SeqTActive);
        }
    }
}

#endif
