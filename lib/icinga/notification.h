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

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

namespace icinga
{

/**
 * The notification type.
 *
 * @ingroup icinga
 */
enum NotificationType
{
	NotificationHost,
	NotificationService
};

class Service;

/**
 * An Icinga notification specification.
 *
 * @ingroup icinga
 */
class I2_ICINGA_API Notification : public DynamicObject
{
public:
	typedef shared_ptr<Notification> Ptr;
	typedef weak_ptr<Notification> WeakPtr;

	Notification(const Dictionary::Ptr& properties);
	~Notification(void);

	static bool Exists(const String& name);
	static Notification::Ptr GetByName(const String& name);

	shared_ptr<Service> GetService(void) const;
	String GetNotificationCommand(void) const;
	Dictionary::Ptr GetMacros(void) const;

	void SendNotification(void);

private:
	set<ScriptTask::Ptr> m_Tasks;

	void NotificationCompletedHandler(const ScriptTask::Ptr& task);
};

}

#endif /* NOTIFICATION_H */