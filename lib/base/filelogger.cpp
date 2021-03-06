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

#include "base/filelogger.h"
#include "base/dynamictype.h"
#include "base/statsfunction.h"
#include <fstream>

using namespace icinga;

REGISTER_TYPE(FileLogger);

REGISTER_STATSFUNCTION(FileLoggerStats, &FileLogger::StatsFunc);

Value FileLogger::StatsFunc(Dictionary::Ptr& status, Dictionary::Ptr& perfdata)
{
	Dictionary::Ptr nodes = make_shared<Dictionary>();

	BOOST_FOREACH(const FileLogger::Ptr& filelogger, DynamicType::GetObjects<FileLogger>()) {
		nodes->Set(filelogger->GetName(), 1); //add more stats
	}

	status->Set("filelogger", nodes);

	return 0;
}

/**
 * Constructor for the FileLogger class.
 */
void FileLogger::Start()
{
	StreamLogger::Start();

	std::ofstream *stream = new std::ofstream();

	String path = GetPath();

	try {
		stream->open(path.CStr(), std::fstream::app | std::fstream::out);

		if (!stream->good())
			BOOST_THROW_EXCEPTION(std::runtime_error("Could not open logfile '" + path + "'"));
	} catch (...) {
		delete stream;
		throw;
	}

	BindStream(stream, true);
}
