/*****************************************************************
 **' InitBattleScene.h
 *****************************************************************
 **' Created on: 25.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef INITBATTLESCENE_H_
#define INITBATTLESCENE_H_

#include <IBattleScene.h>

namespace PKMN
{
	class InitBattleScene : public IBattleScene
	{
	private:
		/**
		 * Time elapsed since scene started. (seconds)
		 */
		float m_elapsedTime;

	public:
		/**
		 * Create new battle init scene.
		 *
		 * @param battle
		 * Parent battle reference.
		 */
		InitBattleScene(Battle &battle);

		/**
		 * Update the init scene. This handles the animation of the appearance
		 * of the enemy as well as the player's pokemon.
		 *
		 * @param kb
		 * Readonly reference to keyboard state.
		 *
		 * @param mouse
		 * Readonly reference to mouse state.
		 *
		 * @param dt
		 * Time passed since last frame in seconds.
		 */
		void update(const Keyboard &kb, const Mouse &mouse, float dt);

		/**
		 * Render the init scene.
		 *
		 * @param window
		 * Window to use for rendering.
		 */
		void render(sf::RenderWindow &window);

		/**
		 * Returns true after all init animations finished.
		 *
		 * @return Whether the init scene has finished.
 		 */
		bool terminated(void);

		/**
		 * Dtor.
		 */
		~InitBattleScene(void);
	};
}



#endif // INITBATTLESCENE_H_
