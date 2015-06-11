/*****************************************************************
 **' TestPokemonGame.h
 *****************************************************************
 **' Created on: 15.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef TESTGAME_H_
#define TESTGAME_H_

#include <IGame.h>

namespace PKMN
{
	/**
	 * Implements a testcase for pokegine.
	 */
	class TestGame : public IGame
	{
	public:
		/**
		 * Default constructor.
		 */
		TestGame(void);

		/**
		 * Create natures and store them inside the database.
		 */
		void createNatures(void);

		/**
		 * One-time setup logic.
		 */
		void onSetup(void) override;

		/**
		 * Actions to be performed once per frame.
		 *
		 * @param dt
		 * Time passed since last frame in seconds.
		 */
		void onUpdate(float dt) override;

		/**
		 * How to render each frame.
		 */
		void onRender(void) override;
	};
}

#endif // TESTGAME_H_
