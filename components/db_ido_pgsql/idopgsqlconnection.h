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

#ifndef IDOPGSQLCONNECTION_H
#define IDOPGSQLCONNECTION_H

#include "db_ido_pgsql/idopgsqlconnection.th"
#include "base/array.h"
#include "base/timer.h"
#include "base/workqueue.h"
#include <libpq-fe.h>

namespace icinga
{

typedef shared_ptr<PGresult> IdoPgsqlResult;

/**
 * An IDO pgSQL database connection.
 *
 * @ingroup ido
 */
class IdoPgsqlConnection : public ObjectImpl<IdoPgsqlConnection>
{
public:
	DECLARE_PTR_TYPEDEFS(IdoPgsqlConnection);
        DECLARE_TYPENAME(IdoPgsqlConnection);

        static Value StatsFunc(Dictionary::Ptr& status, Dictionary::Ptr& perfdata);

protected:
	virtual void Start(void);
	virtual void Stop(void);

	virtual void ActivateObject(const DbObject::Ptr& dbobj);
	virtual void DeactivateObject(const DbObject::Ptr& dbobj);
	virtual void ExecuteQuery(const DbQuery& query);
        virtual void CleanUpExecuteQuery(const String& table, const String& time_key, double time_value);
	virtual void FillIDCache(const DbType::Ptr& type);

private:
	DbReference m_InstanceID;

	WorkQueue m_QueryQueue;

	boost::mutex m_ConnectionMutex;
	PGconn *m_Connection;
	int m_AffectedRows;

	Timer::Ptr m_ReconnectTimer;
	Timer::Ptr m_TxTimer;

	IdoPgsqlResult Query(const String& query);
	DbReference GetSequenceValue(const String& table, const String& column);
	int GetAffectedRows(void);
	String Escape(const String& s);
	Dictionary::Ptr FetchRow(const IdoPgsqlResult& result, int row);

	bool FieldToEscapedString(const String& key, const Value& value, Value *result);
	void InternalActivateObject(const DbObject::Ptr& dbobj);

	void Disconnect(void);
	void NewTransaction(void);
	void Reconnect(void);

	void AssertOnWorkQueue(void);

	void TxTimerHandler(void);
	void ReconnectTimerHandler(void);

	void InternalExecuteQuery(const DbQuery& query, DbQueryType *typeOverride = NULL);
	void InternalCleanUpExecuteQuery(const String& table, const String& time_key, double time_value);

	virtual void ClearConfigTable(const String& table);

	void ExceptionHandler(boost::exception_ptr exp);
};

}

#endif /* IDOPGSQLCONNECTION_H */
