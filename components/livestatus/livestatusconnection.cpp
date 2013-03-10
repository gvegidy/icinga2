/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
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

#include "i2-livestatus.h"

using namespace icinga;

LivestatusConnection::LivestatusConnection(const Stream::Ptr& stream)
	: Connection(stream)
{ }

void LivestatusConnection::ProcessData(void)
{
	String line;
	bool read_line = false;

	while (GetStream()->ReadLine(&line)) {
		read_line = true;

		if (line.GetLength() > 0)
			m_Lines.push_back(line);
		else
			break;
	}

	/* Return if we didn't at least read one line. */
	if (!read_line)
		return;

	/* Return if we haven't found the end of the query. */
	if (line.GetLength() > 0 && !GetStream()->IsReadEOF())
		return;

	LivestatusQuery::Ptr query = boost::make_shared<LivestatusQuery>(m_Lines);
	m_Lines.clear();

	query->Execute(GetStream());
}