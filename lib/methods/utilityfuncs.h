/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-present Icinga Development Team (http://www.icinga.org) *
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

#ifndef UTILITYFUNCS_H
#define UTILITYFUNCS_H

#include "methods/i2-methods.h"
#include "base/qstring.h"
#include "base/array.h"

namespace icinga
{

/**
 * @ingroup methods
 */
class I2_METHODS_API UtilityFuncs
{
public:
	static bool Regex(const String& pattern, const String& text);
	static int Len(const Value& value);
	static Array::Ptr Union(const std::vector<Value>& arguments);
	static Array::Ptr Intersection(const std::vector<Value>& arguments);

private:
	UtilityFuncs(void);
};

}

#endif /* UTILITYFUNCS_H */
