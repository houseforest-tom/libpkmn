/*****************************************************************
 **' IRenderObject.h
 *****************************************************************
 **' Created on: 25.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef IGAMEOBJECT_H_
#define IGAMEOBJECT_H_

#include <Dependencies.h>

namespace PKMN
{
	class IGameObject
	{
	public:
		/**
		 * Update the game object.
		 *
		 * @param kb
		 * Readonly reference to keyboard state.
		 *
		 * @param mouse
		 * Readonly reference to mouse state.
		 *
		 * @param dt
		 * Time in seconds passed since last frame.
		 */
		virtual void update(const Keyboard &kb, const Mouse &mouse, float dt) = 0;

		/**
		 * Render the game object.
		 *
		 * @param window
		 * The render-window to use.
		 */
		virtual void render(RenderWindow &window) = 0;

		/**
		 * Default destructor.
		 */
		virtual ~IGameObject(void)
		{
			NOOP;
		}
	};
}


#endif // IGAMEOBJECT_H_
