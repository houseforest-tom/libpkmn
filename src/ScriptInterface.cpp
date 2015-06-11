/*****************************************************************
 **' ScriptInterface.cpp
 *****************************************************************
 **' Created on: 15.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#include <ScriptInterface.h>

namespace PKMN
{
	ScriptInterface::ScriptInterface(void)
		:m_pScriptEngine(nullptr)
	{
		NOOP;
	}

	/*****************************************************************
	 *****************************************************************/

	void ScriptInterface::messageCallback(const AngelscriptMsgInfo *msg, void *param)
	{
		//Print message type
		switch(msg->type)
		{
			case asMSGTYPE_ERROR:
				cerr << "Angelscript error occurred:" << endl;
			break;

			case asMSGTYPE_WARNING:
				cerr << "Angelscript warning:" << endl;
			break;

			case asMSGTYPE_INFORMATION:
				cerr << "Angelscript information:" << endl;
			break;
		}

		//Print actual message
		cerr << msg->section << "(r: " << msg->row << ", c:" << msg->col << ") : " << msg->message << endl << endl;
	}

	/*****************************************************************
	 *****************************************************************/

	void ScriptInterface::setup(void)
	{
		//Create script interface
		m_pScriptEngine = asCreateScriptEngine(ANGELSCRIPT_VERSION);

		//Register message callback function
		assert(m_pScriptEngine->SetMessageCallback(asMETHOD(ScriptInterface, messageCallback), this, asCALL_THISCALL) >= 0);

		//Register std::string type
		RegisterStdString(m_pScriptEngine);

		//Register math functions
		RegisterScriptMath(m_pScriptEngine);

		//Register print & printhex functions
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(printstr), 		   asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(uint64)", 		   asFUNCTION(printnum<uint64_t>), asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(uint32)", 		   asFUNCTION(printnum<uint32_t>), asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(uint16)", 		   asFUNCTION(printnum<uint16_t>), asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(uint8)", 		   asFUNCTION(printnum<uint8_t>),  asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(int64)", 		   asFUNCTION(printnum<int64_t>),  asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(int32)", 		   asFUNCTION(printnum<int32_t>),  asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(int16)", 		   asFUNCTION(printnum<int16_t>),  asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void print(int8)", 		   	   asFUNCTION(printnum<int8_t>),   asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void printhex(int8)", 		   asFUNCTION(printhex),     	   asCALL_CDECL) >= 0);
		assert(m_pScriptEngine->RegisterGlobalFunction("void printhex(uint8)", 		   asFUNCTION(printhex),     	   asCALL_CDECL) >= 0);

		cout << "Successfully setup script interface." << endl;
	}

	/*****************************************************************
	 *****************************************************************/

	AngelscriptContextID ScriptInterface::createContext(void)
	{
		m_scriptContextPtrs.push_back(m_pScriptEngine->CreateContext());
		cout << "Created script context: " << m_scriptContextPtrs.size() - 1 << endl;
		return m_scriptContextPtrs.size() - 1;
	}

	/*****************************************************************
	 *****************************************************************/

	void ScriptInterface::destroyContext(AngelscriptContextID id)
	{
		cout << "Destroyed script context: " << id << endl;
		m_scriptContextPtrs[id]->Release();
		m_scriptContextPtrs[id] = nullptr;
	}

	/*****************************************************************
	 *****************************************************************/

	AngelscriptModuleID ScriptInterface::createModuleFromFile(const Name &name, const Filename &file)
	{
		AngelscriptBuilder builder;
		builder.StartNewModule(m_pScriptEngine, name.c_str());
		builder.AddSectionFromFile(file.c_str());
		builder.BuildModule();

		cout << "Created script module: " << m_scriptContextPtrs.size() << " (" << name << ")" << endl;
		m_scriptModulePtrs.push_back(m_pScriptEngine->GetModule(name.c_str()));
		return m_scriptModulePtrs.size() - 1;
	}

	/*****************************************************************
	 *****************************************************************/

	AngelscriptModuleID ScriptInterface::createModuleFromCode(const Name &name, const string &code)
	{
		AngelscriptBuilder builder;
		builder.StartNewModule(m_pScriptEngine, name.c_str());
		builder.AddSectionFromMemory("main", code.c_str(), code.length(), 0);
		builder.BuildModule();

		cout << "Created script module: " << m_scriptContextPtrs.size() << " (" << name << ")" << endl;
		m_scriptModulePtrs.push_back(m_pScriptEngine->GetModule(name.c_str()));
		return m_scriptModulePtrs.size() - 1;
	}

	/*****************************************************************
	 *****************************************************************/

	void ScriptInterface::destroyModule(AngelscriptModuleID id)
	{
		cout << "Destroyed script module: " << id << " (" << m_scriptModulePtrs[id]->GetName() << ")" << endl;
		m_scriptModulePtrs[id]->Discard();
		m_scriptModulePtrs[id] = nullptr;
	}

	/*****************************************************************
	 *****************************************************************/

	void ScriptInterface::executeScript(AngelscriptContextID cid, AngelscriptModuleID mid)
	{
		getContext(cid).Prepare(getModule(mid).GetFunctionByDecl("void main(void)"));
		getContext(cid).Execute();
	}

	/*****************************************************************
	 *****************************************************************/

	bool ScriptInterface::existsScriptFunction(AngelscriptModuleID mid, const string &funcdecl)
	{
		return (getModule(mid).GetFunctionByDecl(funcdecl.c_str()) != nullptr);
	}

	/*****************************************************************
	 *****************************************************************/

	void ScriptInterface::prepareScriptFunction(AngelscriptContextID cid, AngelscriptModuleID mid, const string &funcdecl)
	{
		getContext(cid).Prepare(getModule(mid).GetFunctionByDecl(funcdecl.c_str()));
	}

	/*****************************************************************
	 *****************************************************************/

	ScriptInterface::~ScriptInterface(void)
	{
		for(AngelscriptContextID id = 0; id < m_scriptContextPtrs.size(); ++id)
		{
			if(m_scriptContextPtrs[id] != nullptr)
			{
				destroyContext(id);
			}
		}

		for(AngelscriptModuleID id = 0; id < m_scriptModulePtrs.size(); ++id)
		{
			if(m_scriptModulePtrs[id] != nullptr)
			{
				destroyModule(id);
			}
		}

		m_pScriptEngine->ShutDownAndRelease();
		m_pScriptEngine = nullptr;
		cout << "Shut down and released script engine." << endl;
	}
}
