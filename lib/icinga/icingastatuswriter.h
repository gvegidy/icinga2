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

#ifndef ICINGASTATUSWRITER_H
#define ICINGASTATUSWRITER_H

#include "icinga/icingastatuswriter.th"
#include "icinga/host.h"
#include "icinga/service.h"
#include "icinga/command.h"
#include "icinga/compatutility.h"
#include "base/objectlock.h"
#include "base/timer.h"
#include "base/utility.h"
#include <boost/thread/thread.hpp>
#include <iostream>

namespace icinga
{

/**
 * @ingroup compat
 */
class IcingaStatusWriter : public ObjectImpl<IcingaStatusWriter>
{
public:
	DECLARE_PTR_TYPEDEFS(IcingaStatusWriter);
	DECLARE_TYPENAME(IcingaStatusWriter);

	static Value StatsFunc(Dictionary::Ptr& status, Dictionary::Ptr& perfdata);
	static Dictionary::Ptr GetStatusData(void);

protected:
	virtual void Start(void);

private:
	Timer::Ptr m_StatusTimer;
	void StatusTimerHandler(void);
};

}

#endif /* ICINGASTATUSWRITER_H */
