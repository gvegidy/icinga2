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

#ifndef CONFIGCOMPILER_H
#define CONFIGCOMPILER_H

#include "config/i2-config.h"
#include "config/debuginfo.h"
#include "base/registry.h"
#include "base/initialize.h"
#include "base/singleton.h"
#include <iostream>
#include <boost/function.hpp>

namespace icinga
{

/**
 * The configuration compiler can be used to compile a configuration file
 * into a number of configuration items.
 *
 * @ingroup config
 */
class I2_CONFIG_API ConfigCompiler
{
public:
	explicit ConfigCompiler(const String& path, std::istream *input);
	virtual ~ConfigCompiler(void);

	void Compile(void);

	static void CompileStream(const String& path, std::istream *stream);
	static void CompileFile(const String& path);
	static void CompileText(const String& path, const String& text);

	static void AddIncludeSearchDir(const String& dir);

	String GetPath(void) const;

	/* internally used methods */
	void HandleInclude(const String& include, bool search, const DebugInfo& debuginfo);
	void HandleIncludeRecursive(const String& include, const String& pattern, const DebugInfo& debuginfo);
	void HandleLibrary(const String& library);

	size_t ReadInput(char *buffer, size_t max_bytes);
	void *GetScanner(void) const;

private:
	String m_Path;
	std::istream *m_Input;

	void *m_Scanner;

	static std::vector<String> m_IncludeSearchDirs;

	void InitializeScanner(void);
	void DestroyScanner(void);
};

class I2_CONFIG_API ConfigFragmentRegistry : public Registry<ConfigFragmentRegistry, String>
{
public:
	static inline ConfigFragmentRegistry *GetInstance(void)
	{
		return Singleton<ConfigFragmentRegistry>::GetInstance();
	}
};

#define REGISTER_CONFIG_FRAGMENT(id, name, fragment) \
	namespace { \
		void RegisterConfigFragment(void) \
		{ \
			icinga::ConfigFragmentRegistry::GetInstance()->Register(name, fragment); \
		} \
		\
		INITIALIZE_ONCE(RegisterConfigFragment); \
	}

}

#endif /* CONFIGCOMPILER_H */
