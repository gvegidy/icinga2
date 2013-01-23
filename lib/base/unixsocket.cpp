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

#include "i2-base.h"

#ifndef _WIN32
using namespace icinga;

UnixSocket::UnixSocket(void)
{
	int fd = socket(AF_UNIX, SOCK_STREAM, PF_UNIX);

	if (fd < 0)
		throw_exception(PosixException("socket() failed", errno));

	SetFD(fd);
}

void UnixSocket::Bind(const String& path)
{
	unlink(path.CStr());

	sockaddr_un sun = {};
	sun.sun_family = AF_UNIX;
	strncpy(sun.sun_path, path.CStr(), sizeof(sun.sun_path));
	sun.sun_path[sizeof(sun.sun_path) - 1] = '\0';

	if (bind(GetFD(), (sockaddr *)&sun, SUN_LEN(&sun)) < 0)
		throw_exception(PosixException("bind() failed", errno));
}

void UnixSocket::Connect(const String& path)
{
	sockaddr_un sun = {};
	sun.sun_family = AF_UNIX;
	strncpy(sun.sun_path, path.CStr(), sizeof(sun.sun_path));
	sun.sun_path[sizeof(sun.sun_path) - 1] = '\0';

	if (connect(GetFD(), (sockaddr *)&sun, SUN_LEN(&sun)) < 0 && errno != EINPROGRESS)
		throw_exception(PosixException("connect() failed", errno));
}
#endif /* _WIN32 */