/*****************************************************************
 **' IPrintable.h
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef IPRINTABLE_H_
#define IPRINTABLE_H_

#include <Dependencies.h>

namespace PKMN
{
	/**
	 * Interface for classes that shall be able to print information to
	 * the console.
	 */
	class IPrintable
	{
	public:
		/**
		 * Prints sensible information about the current object.
		 */
		virtual void print(void) const = 0;

		/**
		 * Default dtor.
		 */
		virtual ~IPrintable(void)
		{
			NOOP;
		}
	};
}

#endif // IPRINTABLE_H_
