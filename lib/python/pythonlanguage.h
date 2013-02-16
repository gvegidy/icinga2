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

#ifndef PYTHONLANGUAGE_H
#define PYTHONLANGUAGE_H

namespace icinga
{

class PythonInterpreter;

/**
 * The Python scripting language.
 *
 * @ingroup base
 */
class I2_PYTHON_API PythonLanguage : public ScriptLanguage
{
public:
	typedef shared_ptr<PythonLanguage> Ptr;
	typedef weak_ptr<PythonLanguage> WeakPtr;

	PythonLanguage(void);
	~PythonLanguage(void);

	virtual ScriptInterpreter::Ptr CreateInterpreter(const Script::Ptr& script);

	PyThreadState *GetMainThreadState(void) const;

	static PythonInterpreter *GetCurrentInterpreter(void);
	static void SetCurrentInterpreter(PythonInterpreter *interpreter);

	static PyObject *MarshalToPython(const Value& value);
	static Value MarshalFromPython(PyObject *value);

private:
	PyThreadState *m_MainThreadState;
	PyObject *m_NativeModule;
	static PythonInterpreter *m_CurrentInterpreter;

	void RegisterNativeFunction(const String& name, const ScriptFunction::Ptr& function);
	void UnregisterNativeFunction(const String& name);

	static PyObject *PyCallNativeFunction(PyObject *self, PyObject *args);
	static PyObject *PyRegisterFunction(PyObject *self, PyObject *args);

	static PyMethodDef m_NativeMethodDef[];
};

}

#endif /* PYTHONLANGUAGE_H */