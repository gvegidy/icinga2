/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2014 Icinga Development Team (http://www.icinga.org)    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef CIB_H
#define CIB_H

#include "icinga/i2-icinga.h"
#include "base/ringbuffer.h"
#include "base/dictionary.h"

namespace icinga
{

typedef struct {
    double min_latency;
    double max_latency;
    double avg_latency;
    double min_execution_time;
    double max_execution_time;
    double avg_execution_time;
} ServiceCheckStatistics;

typedef struct {
    double services_ok;
    double services_warning;
    double services_critical;
    double services_unknown;
    double services_pending;
    double services_unreachable;
    double services_flapping;
    double services_in_downtime;
    double services_acknowledged;
} ServiceStatistics;

typedef struct {
    double hosts_up;
    double hosts_down;
    double hosts_unreachable;
    double hosts_pending;
    double hosts_flapping;
    double hosts_in_downtime;
    double hosts_acknowledged;
} HostStatistics;

/**
 * Common Information Base class. Holds some statistics (and will likely be
 * removed/refactored).
 *
 * @ingroup icinga
 */
class I2_ICINGA_API CIB
{
public:
	static void UpdateActiveChecksStatistics(long tv, int num);
	static int GetActiveChecksStatistics(long timespan);

	static void UpdatePassiveChecksStatistics(long tv, int num);
	static int GetPassiveChecksStatistics(long timespan);

        static ServiceCheckStatistics CalculateServiceCheckStats(void);
        static ServiceStatistics CalculateServiceStats(void);
        static HostStatistics CalculateHostStats(void);

        static std::pair<Dictionary::Ptr, Dictionary::Ptr> GetFeatureStats(void);

private:
	CIB(void);

	static boost::mutex m_Mutex;
	static RingBuffer m_ActiveChecksStatistics;
	static RingBuffer m_PassiveChecksStatistics;
};

}

#endif /* CIB_H */
