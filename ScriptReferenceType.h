/*****************************************************************
 **' ScriptReferenceType.h
 *****************************************************************
 **' Created on: 15.05.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef SCRIPTREFERENCETYPE_H_
#define SCRIPTREFERENCETYPE_H_

#include <Dependencies.h>

namespace PKMN
{
	class ScriptReferenceType
	{
	public:
		/**
		 * Construct new script reference type.
		 */
		ScriptReferenceType(void){ NOOP; }

		/**
		 * Called upon reference addition.
		 */
		inline void addref (void){ NOOP; }

		/**
		 * Called upon reference removal.
		 */
		inline void release(void){ NOOP; }
	};
}


#endif // SCRIPTREFERENCETYPE_H_
