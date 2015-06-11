/*****************************************************************
 **' PokemonGame.h
 *****************************************************************
 **' Created on: 13.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef IGAME_H_
#define IGAME_H_

#include <Dependencies.h>
#include <Database.h>
#include <Battle.h>
#include <ScriptInterface.h>
#include <Spritebank.h>

namespace PKMN
{
	/**
	 * Base class for a pokemon game
	 */
	class IGame
	{
	private:
		/**
		 * Underlying window used for rendering.
		 */
		RenderWindow m_window;

		/**
		 * Keyboard input device.
		 */
		Keyboard m_keyboard;

		/**
		 * Mouse input device.
		 */
		Mouse m_mouse;

		/**
		 * Clock to measure total elapsed game time.
		 */
		Clock m_elapsedTimeClock;

		/**
		 * Database containing species, moves, abilities, etc.
		 */
		Database m_database;

		/**
		 * Spritebank used to load / store textures and sprites.
		 */
		Spritebank m_spritebank;

		/**
		 * Pointer to current battle. Set to nullptr when there is no
		 * battle currently active.
		 */
		unique_ptr<Battle> m_pBattle;

		/**
		 * Script interface.
		 */
		ScriptInterface m_scriptInterface;

		/**
		 * Expose enumeration types to script interface.
		 */
		void exposeEnumTypes(void);

		/**
		 * Expose reference types to script interface.
		 */
		void exposeReferenceTypes(void);

		/**
		 * Expose global variables & functions to script interface.
		 */
		void exposeGlobals(void);

	public:
		/**
		 * Creates a new pokemon game.
		 *
		 * @param windowWidth
		 * Width of the window to create in pixels.
		 * @param windowHeight
		 * Height of the window to create in pixels.
		 * @param fullscreen
		 * Whether or not the window shall be displayed in full screen mode.
		 * @param title
		 * The title string to display.
		 */
		IGame(unsigned windowWidth, unsigned windowHeight, bool fullscreen, const string &title);

		/**
		 * @return Reference to the underlying window.
		 */
		inline RenderWindow &getWindow(void)
		{
			return m_window;
		}

		/**
		 * @return Const reference to the keyboard.
		 */
		inline const Keyboard &getKeyboard(void) const
		{
			return m_keyboard;
		}

		/**
		 * @return Const reference to the mouse.
		 */
		inline const Mouse &getMouse(void) const
		{
			return m_mouse;
		}

		/**
		 * @return Const reference to the database.
		 */
		inline const Database &getDatabase(void) const
		{
			return m_database;
		}

		/**
		 * @return Mutable reference to the database.
		 */
		inline Database &getDatabase(void)
		{
			return m_database;
		}

		/**
		 * @return Mutable reference to spritebank.
		 */
		inline Spritebank &getSpritebank(void)
		{
			return m_spritebank;
		}

		/**
		 * @return Mutable reference to the scripting interface.
		 */
		inline ScriptInterface &getScriptInterface(void)
		{
			return m_scriptInterface;
		}

		/**
		 * @return Mutable pointer to the current battle.
		 * Returns nullptr if no battle is active.
		 */
		Battle *getBattle(void);

		/**
		 * Set the current battle to the one passed in.
		 *
		 * @param battle
		 * Pointer to the new battle object.
		 */
		void setBattle(Battle *battle);

		/**
		 * @return Total time elapsed since initialization.
		 */
		Time getElapsedTime(void) const;

		/**
		 * Invokes the game's main loop consisting of update and render calls.
		 */
		void run(void);

		/**
		 * Setup hook, all one-time initialization logic, e.g. resource loading should be handled
		 * inside this method.
		 */
		virtual void onSetup(void) = 0;

		/**
		 * Update hook, invoked once per frame.
		 *
		 * @param dt
		 * Time passed since the last frame in seconds.
		 */
		virtual void onUpdate(float dt) = 0;

		/**
		 * Render hook, invoked once per frame.
		 * The screen is cleared beforehand this call and updated afterwards.
		 */
		virtual void onRender(void) = 0;

		/**
		 * Default destructor.
		 */
		virtual ~IGame(void);
	};
}

#endif /* IGAME_H_ */
