/*****************************************************************
 **' ScriptInterface.h
 *****************************************************************
 **' Created on: 15.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef SCRIPTINTERFACE_H_
#define SCRIPTINTERFACE_H_

#include <Dependencies.h>
#include <type_traits>
#include <angelscript.h>
#include <../scriptmath/scriptmath.h>
#include <../scriptarray/scriptarray.h>
#include <../scriptbuilder/scriptbuilder.h>
#include <../scriptstdstring/scriptstdstring.h>

namespace PKMN
{
	/**
	 * Angelscript types.
	 */
	using IAngelscriptEngine 		= asIScriptEngine;			// Engine
	using IAngelscriptModule 		= asIScriptModule;			// Module
	using IAngelscriptContext 		= asIScriptContext;			// Context
	using IAngelscriptGeneric 		= asIScriptGeneric;			// Generic
	using IAngelscriptObject 		= asIScriptObject;			// Object
	using IAngelscriptType 			= asIObjectType;			// Object type
	using IAngelscriptFunction 		= asIScriptFunction;		// Function
	using IAngelscriptJITCompiler 	= asIJITCompiler;			// JIT compiler
	using IAngelscriptBinaryStream	= asIBinaryStream;			// Binary stream
	using IAngelscriptThreadMgr		= asIThreadManager;			// Thread manager
	using IAngelscriptLockShareBool = asILockableSharedBool;	// Lockable shared boolean
	using AngelscriptMsgInfo 		= asSMessageInfo;			// Message info
	using AngelscriptVMRegisters 	= asSVMRegisters;			// VM registers
	using AngelscriptBytecodeInfo	= asSBCInfo;				// Bytecode instruction information

	template<int SIZE>
	using AngelscriptMethodPtr   	= asSMethodPtr<SIZE>;		// Method pointer
	using AngelscriptFunctionPtr 	= asSFuncPtr;				// Function pointer

	using AngelscriptBuilder		= CScriptBuilder;			// Script builder
	using AngelscriptContextID		= unsigned;					// Script context ID
	using AngelscriptModuleID		= unsigned;					// Script module ID

	/**
	 * Wrapper class for angelscript interface.
	 * Provides various helper functions.
	 */
	class ScriptInterface
	{
	private:

		/**
		 * Angelscript engine.
		 */
		IAngelscriptEngine *m_pScriptEngine;

		/**
		 * Created script contexts.
		 */
		vector<IAngelscriptContext*> m_scriptContextPtrs;

		/**
		 * Created script modules.
		 */
		vector<IAngelscriptModule*> m_scriptModulePtrs;

		/**
		 * Angelscript message callback.
		 *
		 * @param msg
		 * Angelscript message info.
		 *
		 * @param param
		 * Additional parameter(s).
		 */
		void messageCallback(const AngelscriptMsgInfo *msg, void *param);

	public:

		/**
		 * Default constructor.
		 */
		ScriptInterface(void);

		/**
		 * Setup the script interface.
		 */
		void setup(void);

		/**
		 * Creates a script context and returns the resulting ID.
		 */
		AngelscriptContextID createContext(void);

		/**
		 * Returns a script context.
		 *
		 * @param id
		 * Context ID.
		 *
		 * @return
		 * Context of given ID.
		 */
		inline IAngelscriptContext &getContext(AngelscriptContextID id)
		{
			return *m_scriptContextPtrs[id];
		}

		/**
		 * Destroys an existing script context.
		 *
		 * @param id
		 * Context ID.
		 */
		void destroyContext(AngelscriptContextID id);

		/**
		 * Creates a script module and returns the result.
		 *
		 * @param name
		 * Name of the module to create.
		 *
		 * @param file
		 * Name of the script file.
		 */
		AngelscriptModuleID createModuleFromFile(const Name &name, const Filename &file);

		/**
		 * Creates a script module and returns the result.
		 *
		 * @param name
		 * Name of the module to create.
		 *
		 * @param code
		 * Source code of the module.
		 */
		AngelscriptModuleID createModuleFromCode(const Name &name, const string &code);

		/**
		 * Destroys an existing script module.
		 *
		 * @param id
		 * Module ID.
		 */
		void destroyModule(AngelscriptModuleID id);

		/**
		 * Returns a script module.
		 */
		inline IAngelscriptModule &getModule(AngelscriptModuleID id)
		{
			return *m_scriptModulePtrs[id];
		}

		/**
		 * Uses the specified context to execute the main function
		 * of the given module.
		 *
		 * @param cid
		 * ID of the context to use.
		 *
		 * @param mid
		 * ID of the module to run the main function of.
		 */
		void executeScript(AngelscriptContextID cid, AngelscriptModuleID mid);

		/**
		 * Checks whether or not a function matching the declaration exists
		 * inside the specified module.
		 *
		 * @param mid
		 * ID of the module.
		 *
		 * @param funcdecl
		 * Function declaration in script function.
		 *
		 * @return
		 * Whether it exists.
		 */
		bool existsScriptFunction(AngelscriptModuleID mid, const string &funcdecl);

		/**
		 * Prepares the specified script context for a call to the function
		 * inside the given module that fits the declaration.
		 *
		 * @param cid
		 * ID of the context to use.
		 *
		 * @param mid
		 * ID of the module.
		 *
		 * @param funcdecl
		 * Function declaration in script function.
		 */
		void prepareScriptFunction(AngelscriptContextID cid, AngelscriptModuleID mid, const string &funcdecl);

		/**
		 * Executes the prepared script function.
		 *
		 * @param cid
		 * Context ID.
		 *
		 * @return
		 * Result code. Consult angelscript documentation for further details.
		 */
		inline int executeScriptFunction(AngelscriptContextID cid){ return getContext(cid).Execute(); }

		/**
		 * Wrapper function to set argument values inside a given script context.
		 *
		 * @param cid
		 * ID of the context.
		 *
		 * @param arg
		 * ID of the argument to set (0,..)
		 *
		 * @param value
		 * Value of the argument.
		 */
		template<typename T>
		void setScriptFunctionArg(AngelscriptContextID cid, unsigned arg, T value)
		{
			void *raw = (void *)(& value);

			//Pointer argument
			if(is_pointer<T>())
				getContext(cid).SetArgObject(arg, *(void **)raw);

			//Boolean argument
			else if(equal<T, bool>())
				getContext(cid).SetArgByte(arg, *(asBYTE *)raw);

			//Byte argument
			else if(equal<T, int8_t>() || equal<T, uint8_t>())
				getContext(cid).SetArgByte(arg, *(asBYTE *)raw);

			//Word argument
			else if(equal<T, int16_t>() || equal<T, uint16_t>())
				getContext(cid).SetArgWord(arg, *(asWORD *)raw);

			//DWord argument
			else if(equal<T, int32_t>() || equal<T, uint32_t>())
				getContext(cid).SetArgDWord(arg, *(asDWORD *)raw);

			//QWord argument
			else if(equal<T, int64_t>() || equal<T, uint64_t>())
				getContext(cid).SetArgQWord(arg, *(asQWORD *)raw);

			//Float argument
			else if(equal<T, float>())
				getContext(cid).SetArgFloat(arg, *(float *)raw);

			//Double argument
			else if(equal<T, double>())
				getContext(cid).SetArgDouble(arg, *(double *)raw);
		}

		/**
		 * Return the result of the previously executed script function.
		 *
		 * @param cid
		 * Context ID.
		 *
		 * @return
		 * Return value interpreted as type T.
		 */
		template<typename T>
		T getScriptFunctionResult(AngelscriptContextID cid)
		{
			return *(T *)getContext(cid).GetAddressOfReturnValue();
		}

		/**
		 * Expose a reference type to the script interface.
		 *
		 * @param name
		 * Name to use for the exposed type.
		 *
		 * @return True on success, false otherwise.
		 */
		template<typename T>
		bool exposeReferenceType(const Name &name)
		{
			const char *cstr = name.c_str();
			if(m_pScriptEngine->RegisterObjectType(cstr, 0, asOBJ_REF) < 0) return false;
			if(m_pScriptEngine->RegisterObjectBehaviour(cstr, asBEHAVE_ADDREF,  "void f(void)", asMETHOD(T, addref),  asCALL_THISCALL) < 0) return false;
			if(m_pScriptEngine->RegisterObjectBehaviour(cstr, asBEHAVE_RELEASE, "void f(void)", asMETHOD(T, release), asCALL_THISCALL) < 0) return false;
			return true;
		}

		/**
		 * Expose a type's member function to the script interface.
		 *
		 * @param name
		 * Name to use for the exposed member function.
		 *
		 * @param scriptDecl
		 * Declaration in script language.
		 *
		 * @return True on success, false otherwise.
		 */
		template<typename MEMBER>
		bool exposeMemberFunction(const Name &type, const string &scriptDecl, const MEMBER &memberfn)
		{
			if(m_pScriptEngine->RegisterObjectMethod(type.c_str(), scriptDecl.c_str(), memberfn, asCALL_THISCALL) < 0) return false;
			return true;
		}

		/**
		 * Expose a type's publicly accessible field to the script interface.
		 *
		 * @param name
		 * Name to use for the exposed member function.
		 *
		 * @param scriptDecl
		 * Declaration in script language.
		 *
		 * @param offset
		 * Field offset in bytes.
		 *
		 * @return True on success, false otherwise.
		 */
		inline bool exposeField(const Name &type, const string &scriptDecl, unsigned offset)
		{
			if(m_pScriptEngine->RegisterObjectProperty(type.c_str(), scriptDecl.c_str(), offset) < 0) return false;
			return true;
		}

		/**
		 * Expose a global variable.
		 *
		 * @param scriptDecl
		 * Declaration in script language.
		 *
		 * @param global
		 * The global variable address.
		 *
		 * @return True on success, false otherwise.
		 */
		inline bool exposeGlobal(const string &scriptDecl, void *global)
		{
			if(m_pScriptEngine->RegisterGlobalProperty(scriptDecl.c_str(), global) < 0) return false;
			return true;
		}

		/**
		 * Expose a global function.
		 *
		 * @param scriptDecl
		 * Declaration in script language.
		 *
		 * @param fn
		 * The function pointer.
		 *
		 * @return True on success, false otherwise.
		 */
		inline bool exposeGlobalFunction(const string &scriptDecl, AngelscriptFunctionPtr fn)
		{
			if(m_pScriptEngine->RegisterGlobalFunction(scriptDecl.c_str(), fn, asCALL_CDECL) < 0) return false;
			return true;
		}

		/**
		 * Expose a typedef statement to create an alias for an exposed type.
		 *
		 * @param alias
		 * The new alias to define.
		 *
		 * @param type
		 * The original type.
		 *
		 * @return True on success, false otherwise.
		 */
		inline bool exposeTypeAlias(const string &alias, const string &type)
		{
			if(m_pScriptEngine->RegisterTypedef(alias.c_str(), type.c_str()) < 0) return false;
			return true;
		}

		/**
		 * Expose an enumeration type.
		 *
		 * @param name
		 * Enum name.
		 *
		 * @param values
		 * List of values to register {{name, value},..}.
		 *
		 * @return True on success, false otherwise.
		 */
		template<typename E>
		bool exposeEnumType(const Name &name, const map<Name, E> &values)
		{
			int result;
			if((result = m_pScriptEngine->RegisterEnum(name.c_str())) < 0)
			{
				switch(result)
				{
					case asINVALID_NAME: 		cout << "Enumeration name " << name << " is invalid." << endl; 				break;
					case asALREADY_REGISTERED: 	cout << "Enumeration name " << name << " is already registered." << endl; 	break;
					case asERROR: 				cout << "Enumeration name could not be parsed." << endl; 					break;
					case asNAME_TAKEN: 			cout << "Enumeration name " << name << " is already taken." << endl; 		break;
					default: 					cout << "Unknown error during registration of " << name << "." << endl;		break;
				}

				return false;
			}

			for(auto iter = values.begin(); iter != values.end(); ++iter)
			{
				if(m_pScriptEngine->RegisterEnumValue(name.c_str(), iter->first.c_str(), (int)iter->second) < 0) return false;
			}

			return true;
		}

		/**
		 * Discard modules and release contexts.
		 */
		~ScriptInterface(void);

		//Generic wrapper function for numeric value console output from script.
		template<typename T>
		static inline void printnum(const T &value)
		{
			if(is_same<T, uint8_t>::value) cout << (unsigned)value;
			else cout << value;
		}

		//Wrapper function for console output from script. (string)
		static inline void printstr(const string &value){ cout << value; }

		//Wrapper function for console output from script. (hex (uint8))
		static inline void printhex(uint8_t value){ printf("0x%02x", value); }

		//Resolves to enumeration types tostring function address
		#define ENUM_TOSTRING_FUNC(E) (__ ## E ## __::tostring)
	};
}

#endif // SCRIPTINTERFACE_H_
