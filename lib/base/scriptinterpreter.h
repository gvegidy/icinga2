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

#ifndef SCRIPTINTERPRETER_H
#define SCRIPTINTERPRETER_H

#include "base/i2-base.h"
#include "base/script.h"
#include <vector>
#include <set>

namespace icinga
{

/**
 * A script interpreter.
 *
 * @ingroup base
 */
class I2_BASE_API ScriptInterpreter : public Object
{
public:
	DECLARE_PTR_TYPEDEFS(ScriptInterpreter);

	~ScriptInterpreter(void);

protected:
	ScriptInterpreter(const Script::Ptr& script);

	virtual Value ProcessCall(const String& function, const std::vector<Value>& arguments) = 0;

	void SubscribeFunction(const String& name);
	void UnsubscribeFunction(const String& name);

private:
	std::set<String> m_SubscribedFunctions;
};

}

#endif /* SCRIPTINTERPRETER_H */
